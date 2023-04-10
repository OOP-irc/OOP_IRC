/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:37:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/04/10 18:53:57 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/Server.hpp"

Server::Server(const std::string &port, const std::string &password)
    : mHost("127.0.0.1"), mPort(port), mPassword(password)
{
    mSock = createSocket();
    mParser = new Parser(this);
}

Server::~Server()
{
	delete mParser;

    {
        channel_iterator start = mChannels.begin();
        channel_iterator end = mChannels.end();

        while (start != end)
        {
            delete start->second;
            ++start;
        }
        mChannels.clear();
    }

    {
        client_iterator start = mClients.begin();
        client_iterator end = mClients.end();

        while (start != end)
        {
            delete start->second;
            ++start;
        }
        mClients.clear();
    }
}

/* Initialize and Listen */

void            Server::Start()
{
	// add the server to the poll
	pollfd srv = {mSock, POLLIN, 0};
	mPollFd.push_back(srv);

	Log::log("Server is listening...");
	while (1)
	{
		if (poll(mPollFd.begin().base(), mPollFd.size(), -1) < 0)
			throw std::runtime_error("Error while polling from fd!");

		for (pfd_iterator it = mPollFd.begin(); it != mPollFd.end(); it++)
		{
			if (it->revents == 0)
				continue;

			if ((it->revents & POLLHUP) == POLLHUP)
			{
				this->OnClientDisconnect(it->fd);
				break;
			}

			if ((it->revents & POLLIN) == POLLIN)
			{
				if (it->fd == mSock)
				{
					this->onClientConnect();
					break;
				}

				this->onClientMessage(it->fd);
			}
		}
	}
}

/* Handle Clients */

void            Server::onClientConnect()
{
    int         fd;
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);

    // accept()로 서버 소켓과 연결된 클라이언트의 fd 생성

    fd = accept(mSock, (sockaddr *) &addr, &size);
    if (fd < 0)
        throw std::runtime_error("Error while accepting a new client!");

    // 클라이언트의 fd를 poll 목록에 추가
    pollfd  pollFd = {fd, POLLIN, 0};
    mPollFd.push_back(pollFd);

    // getting hostname from the client address
    char hostname[NI_MAXHOST];

	// 클라이언트의 IP주소에서 호스트네임을 가져온다.
    int res = getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
    if (res != 0)
        throw std::runtime_error("Error while getting a hostname on a new client!");

    // 클라이언트 만들고 저장

    Client* client = new Client(fd, ntohs(addr.sin_port), hostname);
    mClients.insert(std::make_pair(fd, client));

    // 로그 출력

    /// char message[1000];
    /// sprintf(message, "%s:%d has connected.", client->GetHostname().c_str(), client->GetPort());
    /// Log::log(message);
}

void            Server::OnClientDisconnect(int fd)
{
    try
    {
        // 클라이언트를 찾고  제거
        Client* client = mClients.at(fd);
        if (client == NULL)
        {
            ///Log::log("client already exit");
            return ;
        }

        client->LeaveAllChannel();
        removeClientOnServerAndLog(fd, client);

        // pollfd 목록에서 제거

        pfd_iterator it_b = mPollFd.begin();
        pfd_iterator it_e = mPollFd.end();

        while (it_b != it_e)
        {
            if (it_b->fd == fd)
            {
                mPollFd.erase(it_b);
                close(fd);
                break;
            }
            it_b++;
        }
    }
    catch (const std::exception &e)
    {
        /// std::cout << "Error while disconnecting! " << e.what() << std::endl;
    }
}

void            Server::onClientMessage(int fd)
{
    try
    {
        Client*     client = mClients.at(fd);
        std::string message = this->readMessage(client, fd);

        if (message.size() == 0)
        {
            return ;
        }
        mParser->Invoke(client, message);
    }
    catch (const std::exception& e)
    {
        /// std::cout << "Error while handling the client message! " << e.what() << std::endl;
    }
}

std::string     Server::readMessage(Client *client, int fd)
{
    std::string message;
    char buffer[100];
	memset(buffer, 0, 100);

    if (client->GetSilcedMsg().length() != 0)
    {
        message.append(client->GetSilcedMsg());
        client->SetSilcedMsg("");
    }
	memset(buffer, 0, 100);
    // EWOULDBLOCK은 아직은 클라이언트가 write를 하지 않았음을 의미
    if ((recv(fd, buffer, 100, 0) < 0) and (errno != EWOULDBLOCK))
    {
        throw std::runtime_error("Error while reading buffer from a client!");
    }
    if (!strstr(buffer, "\n"))
    {
        client->SetSilcedMsg(message + buffer);
        return "";
    }
    else
    {
        message.append(buffer);
    }
    return message;
}

void            Server::removeClientOnServerAndLog(int fd, Client *client)
{
    ///char message[1000];
    ///sprintf(message, "%s:%d has disconnected!", client->GetHostname().c_str(), client->GetPort());
    ///Log::log(message);

    delete client;

    mClients.erase(fd);
}

// 서브젝트 조건에 맞는 소켓을 만든 이후 그 소켓의 fd값을 반환한다.
int             Server::createSocket()
{
    // Descriptor
    // opening a socket
	// AF_INET == IPV4  SOCK_STREAM == stream socket
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0)
        throw std::runtime_error("Error while opening a socket!");

    // 포트에 소켓을 강제로 연결하여 재사용 가능하게 만드는 것
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


/* Getters */

std::string     Server::GetPassword() const
{
    return mPassword;
}

Client*         Server::GetClientNickname(const std::string& nickname)
{
    client_iterator it_b = mClients.begin();
    client_iterator it_e = mClients.end();

    while (it_b != it_e)
    {
        if (!nickname.compare(it_b->second->GetNickname()))
            return it_b->second;

        it_b++;
    }

    return NULL;
}

Channel*        Server::GetChannel(const std::string& name)
{
    channel_iterator it = mChannels.find(name);

    if (it != mChannels.end())
    {
        return it->second;
    }

    return NULL;
}

Channel*        Server::CreateChannel(const std::string &name, const std::string &password, Client *client)
{
    Channel *newChan = new Channel(name, password, client);
    assert(newChan != NULL);

    mChannels.insert(std::pair<std::string, Channel *>(name, newChan));

    return newChan;
}
