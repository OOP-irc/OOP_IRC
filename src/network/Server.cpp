/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:37:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/24 19:58:21 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/Server.hpp"

Server::Server(const std::string &port, const std::string &password)
    : mHost("127.0.0.1"), mPort(port), mPassword(password)
{
    mSock = create_socket();
    // _parser = new Parser(this);
}

Server::~Server()
{
	// delete _parser;

    for (size_t i = 0; i < _channels.size(); i++)
        delete mClients[i];

}

// 서브젝트 조건에 맞는 소켓을 만든 이후 그 소켓의 fd값을 반환한다.
int             Server::create_socket()
{

    // Descriptor
    // opening a socket
	// AF_INET  SOCK_STREAM == stream socket
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

    bzero((char*) &serverAddr, sizeof(serverAddr));
    
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
