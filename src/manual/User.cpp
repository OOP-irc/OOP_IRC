/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 19:24:03 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

User::User(Server* server, bool auth) : Manual(server, auth) {}

User::~User() {}

// syntax : USER <user> <mode> <unused> <realname>
// syntax : USER <user> <mode>  *  :<realname>
// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

void    User::Execute(Client* client, std::vector<std::string> args)
{
    if (client->GetState() == REGISTERED)
    {
        client->SendErrorToClient(ERR_ALREADYREGISTRED(client->GetNickname()));
        return;
    }

    if (args.size() < 4) 
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "USER"));
        return;
    }
    
    client->SetUsername(args[0]);
    client->SetRealname(args[3]);
    
    client->TryClientLogin();
}
