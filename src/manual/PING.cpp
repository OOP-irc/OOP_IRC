/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:49:40 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 17:23:31 by mikim3           ###   ########.fr       */
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
		client->Reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "PING"));
		return ;
	}

	client->Write(RPL_PING(client->GetPrefix(), args.at(0)));
}
