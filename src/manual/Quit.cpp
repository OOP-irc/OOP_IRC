/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:49:40 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 17:11:23 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Quit::Quit(Server* server, bool auth) : Manual(server, auth) {}

Quit::~Quit() {}

// syntax: Quit [<message>]

void	Quit::Execute(Client* client, std::vector<std::string> args)
{
	std::string reason = args.empty() ? "Leaving..." : args.at(0);

	// 클라이언트 형식에 따라 ':'가 붙어서 올때가 있는거 처리
	if (reason.at(0) == ':')
        reason = reason.substr(1);

    client->trySend(RPL_QUIT(client->GetPrefix(), reason));
	
	// onClientDisconnect를 실행하면 클라이언트가 자체적으로 끊어버리는 경우도 있어서
	// 이미 나간 클라이인트를 서버가 또 Disconnect하는 경우가 발생한다. 어쩔수 없다.
	// private 여서 안되나?? 나중에 다시보기
	mServer->onClientDisconnect(client->GetFd());

}
