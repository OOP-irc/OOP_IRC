/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/04/03 10:55:01 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Nick::Nick(Server* server, bool auth)
    : Manual(server, auth)
{
}

Nick::~Nick()
{
}

// syntax : NICK <nickname>

void    Nick::Execute(Client*   client, std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "NICK"));
        return ;
    }


    if (args.empty() || args[0].empty())
    {
        client->SendErrorToClient(Log::GetERRNONICKNAMEGIVEN(client->GetPrefix(), client->GetNickname()));
        return ;
    }

    std::string nickname = args[0];

    if (mServer->GetClientNickname(nickname))
    {
        client->SendErrorToClient(Log::GetERRNICKNAMEINUSE(client->GetPrefix(), client->GetNickname()));
        return ;
    }

    client->SetNickname(nickname);
    client->TryClientLogin();
}
