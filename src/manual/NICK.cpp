/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 15:32:36 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Nick::Nick(Server* server, bool auth) : Manual(server, auth) {}

Nick::~Nick() {}

// syntax : NICK <nickname>

void    Nick::execute(Client*   client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty())
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->GetNickname()));
        return ;
    }

    std::string nickname = args[0];

    if (mServer->GetClient(nickname))
    {
        client->reply(ERR_NICKNAMEINUSE(client->GetNickname()));
        return ;
    }
    
    client->SetNickname(nickname);
    client->welcome();
}






