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
	if (args.size() > 1)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "QUIT"));
        return;
    }
	
	std::string reason = args.empty() ? "Leaving..." : args.at(0);

	// 클라이언트 형식에 따라 ':'가 붙어서 올때가 있는거 처리
	if (reason.at(0) == ':')
        reason = reason.substr(1);

    client->SendErrorToClient(Log::GetRPLQUIT(client->GetPrefix(), reason));

    mServer->OnClientDisconnect(client->GetFd());
}
