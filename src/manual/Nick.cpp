/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 19:38:57 by mikim3           ###   ########.fr       */
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
// ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
// ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
// ERR_UNAVAILRESOURCE             ERR_RESTRICTED

void    Nick::Execute(Client*   client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty())
    {
        client->SendErrorToClient(ERR_NONICKNAMEGIVEN(client->GetNickname()));
        return ;
    }

    std::string nickname = args[0];

    if (mServer->GetClient(nickname))
    {
        client->SendErrorToClient(ERR_NICKNAMEINUSE(client->GetNickname()));
        return ;
    }
    
    // ERR_ERRONEUSNICKNAME 잘못된 형식의 닉네임 (구현예정)

    client->SetNickname(nickname);
    client->Welcome();
}
