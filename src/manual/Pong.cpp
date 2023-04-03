/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/04/03 10:57:57 by mikim3           ###   ########.fr       */
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
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "PONG"));
        return ;
    }

    client->SendErrorToClient(Log::GetRPLPING(client->GetPrefix(), args.at(0)));
}
