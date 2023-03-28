/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 13:54:42 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Pass::Pass(Server* server) : Manual(server, auth) {}

Pass::~Pass() {}

// syntax: PASS <password>

void    Pass::Execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        clinet->reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "PASS"));
        return ;
    }

    if (client->IsRegistered())
    {
        client->Reply(ERR_ALREADYREGISTERED(client->GetNickname()));
        return ;
    }

    if (mServer->GetPassword() != args[0].substr(args[0][0] == ':' ? 1 : 0))
    {
        client->reply(ERR_PASSWDMISMATCH(client->GetNickname()));
        return ;
    }

    client->SetState(LOGIN);
}

