/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 16:34:36 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Nick::Nick(Server* server, bool auth) : Manual(server, auth) {}

Nick::~Nick() {}

// syntax : NICK <nickname>
// ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
// ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
// ERR_UNAVAILRESOURCE             ERR_RESTRICTED


void    Nick::Execute(Client*   client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty())
    {
        client->Reply(ERR_NONICKNAMEGIVEN(client->GetNickname()));
        return ;
    }

    std::string nickname = args[0];

    if (mServer->GetClient(nickname))
    {
        client->Reply(ERR_NICKNAMEINUSE(client->GetNickname()));
        return ;
    }
    
    // ERR_NICKCOLLISION 이미 사용중인 닉네임

    // ERR_ERRONEUSNICKNAME 잘못된 형식의 닉네임
    // ERR_UNAVAILRESOURCE 현재 사용가능한 자원이 없음

    // ERR_RESTRICTED 해당 작업을 수행할 권한이 없음

    client->SetNickname(nickname);
    client->Welcome();
}
