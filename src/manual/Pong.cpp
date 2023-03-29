/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 15:32:40 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Pong::Pong(Server* server) : Manual(server) {}

Pong::~Pong() {}

// syntax: PONG <server1> [<server2>]
// ERR_NOORIGIN ERR_NOSUCHSERVER //둘다 ft_irc에서 구현 불가능

void    Pong::Execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->Reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "PONG"));
        return ;
    }

    client->Write(RPL_PING(client->GetPrefix(), args.at(0)));
}
