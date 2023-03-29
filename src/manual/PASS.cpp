/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 14:44:58 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

// auth 필요한지 고민됨
Pass::Pass(Server* server, bool auth) : Manual(server, auth) {}

Pass::~Pass() {}

// syntax: PASS <password>

void    Pass::Execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        clinet->Reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "PASS"));
        return ;
    }

    if (client->IsRegistered())
    {
        client->Reply(ERR_ALREADYREGISTRED(client->GetNickname()));
        return ;
    }

    if (mServer->GetPassword() != args[0].substr(args[0][0] == ':' ? 1 : 0))
    {
        client->Reply(ERR_PASSWDMISMATCH(client->GetNickname()));
        return ;
    }

    client->SetState(LOGIN);
}
