/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:37:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/25 17:45:09 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/Server.hpp"

Server::Server(const std::string &port, const std::string &password)
    : mHost("127.0.0.1"), mPort(port), mPassword(password)
{
    mSock = createSocket();
    // _parser = new Parser(this);
}

Server::~Server()
{
	// delete _parser;

    for (size_t i = 0; i < _channels.size(); i++)
        delete mClients[i];

}

/* Handle Clients */

void            Server::onClientConnect()
{
    // accept a connection

    int         fd;
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);

    fd = accept(mSock, (sockaddr *) &addr, &size);
    if (fd < 0)
        throw std::runtime_error("Error while accepting a new client!");

    // including the client fd in the poll

    pollfd  pollFd = {fd, POLLIN, 0};
    mPollFds.push_back(pollFd);

    // getting hostname from the client address

    char hostname[NI_MAXHOST];
    int res = getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
    if (res != 0)
        throw std::runtime_error("Error while getting a hostname on a new client!");

    // creating and saving a new client

    Client* client = new Client(fd, ntohs(addr.sin_port), hostname);
    mClients.insert(std::make_pair(fd, client));

    // logging connect message

    char message[1000];
    sprintf(message, "%s:%d has connected.", client->GetHostname().c_str(), client->GetPort());
    log(message);
}

void            Server::onClientDisconnect(int fd)
{
    try
    {
        // finding the client and removing

        Client* client = mClients.at(fd);

        client->Leave();

        // log about disconnecting 

        char message[1000];
		sprintf(message, "%s:%d has disconnected!", client->GetHostname().c_str(), client->GetPort());
		log(message);

        mClients.erase(fd);

        // removing the client fd from the poll

        pfd_iterator it_b = mPollFds.begin();
        pfd_iterator it_e = mPollFds.end();

        while (it_b != it_e)
        {
            if (it_b->fd == fd)
            {
                mPollFds.erase(it_b);
                close(fd);
                break;
            }
            it_b++;
        }
        // release memory
        delete client;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error while disconnecting! " << e.what() << std::endl;
    }
}

void            Server::onClientMessage(int fd)
{
    try
    {
        Client*     client = mClients.at(fd);
        std::string message = this->readMessage(fd);
        
        mParser->Invoke(client, message);
    }
    catch (const std::exception& e) 
    {
        std::cout << "Error while handling the client message! " << e.what() << std::endl;
    }
}

std::string     Server::readMessage(int fd)
{
    std::string message;
    
    char buffer[100];
	memset(buffer, 0, 100);

    while (!strstr(buffer, "\n"))
    {
		memset(buffer, 0, 100);
        // EWOULDBLOCK은 아직은 클라이언트가 write를 하지 않았음을 의미
         if ((recv(fd, buffer, 100, 0) < 0) and (errno != EWOULDBLOCK))
            throw std::runtime_error("Error while reading buffer from a client!");

        message.append(buffer);
    }

    return message;
}

// 서브젝트 조건에 맞는 소켓을 만든 이후 그 소켓의 fd값을 반환한다.
int             Server::createSocket()
{
    // Descriptor
    // opening a socket
	// AF_INET  SOCK_STREAM == stream socket
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0)
        throw std::runtime_error("Error while opening a socket!");

    // 포트에 소켓을 강제로 연결하여 재사용 가능하게 만드는 것 
	// 한 클라이언트를 받고 다음 클라이언트를 받으려고 할때 에러가 나버린다.?
    int optionValue = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue)))
        throw std::runtime_error("Error while setting socket options!");

    // 소켓을 NON-BLOCKING 모드로 만드는 것
    if (fcntl(socketFd, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");
    
	// 바인딩을 위해 필요한 데이터 수집
    struct sockaddr_in  serverAddr = {};
    memset((char*) &serverAddr, 0, sizeof(serverAddr));
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(atoi(mPort.c_str()));

    // 선택한 포트에서 IP 주소에 소켓을 바인딩하는 것
    if (bind(socketFd, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
        throw std::runtime_error("Error while binding a socket!");

    // 요청을 기다리는 것
    if (listen(socketFd, MAX_CONNECTIONS) < 0)
        throw std::runtime_error("Error while listening on a socket!");

    return socketFd;
}
