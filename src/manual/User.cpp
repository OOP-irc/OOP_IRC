/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 17:24:55 by mikim3           ###   ########.fr       */
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
    if (client->IsRegistered())
    {
        client->Reply(ERR_ALREADYREGISTRED(client->GetNickname()));
        return;
    }

    if (args.size() < 4) 
    {
        client->Reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "USER"));
        return;
    }

    if ((args[2] & 12) == 8)
    {
        // 모드를 i 모드로 변경
    }
    else if ((args[2] & 12) == 4)
    {
        // 모드를 w 모드로 변경
    }
    
    client->SetUsername(args[0]);
    client->SetRealname(args[3]);
    client->Welcome();

}
