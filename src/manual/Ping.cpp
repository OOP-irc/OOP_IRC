/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:49:40 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 17:10:40 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Ping::Ping(Server* server) : Manual(server) {}

Ping::~Ping() {}

// syntax: PING <server1> [<server2>]
// ERR_NOORIGIN ERR_NOSUCHSERVER //둘다 ft_irc에서 구현 불가능

void	Ping::Execute(Client* client, std::vector<std::string> args)
{
	if (args.empty())
	{
		client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "PING"));
		return ;
	}

	client->SendErrorToClient(Log::GetRPLPING(client->GetPrefix(), args.at(0)));
}
