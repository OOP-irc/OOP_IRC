/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 19:57:22 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

// auth 필요한지 고민됨
Pass::Pass(Server* server, bool auth) : Manual(server, auth) {}

Pass::~Pass() {}

// syntax: PASS <password>

void    Pass::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "PASS"));
        return ;
    }

    if (client->GetState() == REGISTERED || client->GetState() == LOGIN)
    {
        client->SendErrorToClient(Log::GetERRALREADYREGISTRED(client->GetPrefix(), client->GetNickname()));
        return ;
    }

    if (mServer->GetPassword() != args[0].substr(args[0][0] == ':' ? 1 : 0))
    {
        client->SendErrorToClient(Log::GetERRPASSWDMISMATCH(client->GetPrefix(), client->GetNickname()));
        return ;
    }

    client->SetState(LOGIN);
    client->TryClientLogin();
}
