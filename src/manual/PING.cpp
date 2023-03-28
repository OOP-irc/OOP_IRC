/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:49:40 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 13:39:42 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Ping::Ping(Server* server) : Manual(server) {}

Ping::~Ping() {}

// syntax: PING <server1> [<server2>]

void	Ping::Execute(Client* client, std::vector<std::string> args)
{
	if (args.empty())
	{
		// 클라이언트에게 문자 보내기
		client->reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "PING"));
		return ;
	}

	client->write(RPL_PING(client->GetPrefix(), args.at(0)));
}
