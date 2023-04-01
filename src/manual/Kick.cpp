/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:47:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/30 14:02:19 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Kick::Kick(Server* server) 
    : Manual(server) 
{
}

Kick::~Kick() 
{
}

// syntax: KICK <channel> <client> :[<message>]

void    Kick::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "KICK"));
        return;
    }

    std::string channelName = args[0];
    std::string clientName = args[1];

    std::string reason = "No reason specified!";


    if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
    {
        reason = "";

        std::vector<std::string>::iterator it = args.begin();
        std::vector<std::string>::iterator end = args.end();

        while (it != end)
        {
			reason.append(*it + " ");
            it++;
        }
    }

    

    // Channel *channel = client->get_channel();
    // if (!channel || channel->get_name() != channelName)
    // {
    //     client->reply(ERR_NOTONCHANNEL(client->get_nickname(), channelName));
    //     return;
    // }

    // if (channel->get_admin() != client)
    // {
    //     client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), channelName));
    //     return;
    // }

    // Client *dest = _srv->get_client(clientName);
    // if (!dest)
    // {
    //     client->reply(ERR_NOSUCHNICK(client->get_nickname(), clientName));
    //     return;
    // }

    // if (!dest->get_channel() || dest->get_channel() != channel)
    // {
    //     client->reply(ERR_USERNOTINCHANNEL(client->get_nickname(), dest->get_nickname(), channelName));
    //     return;
    // }

    // // if everything is fine
    // channel->kick(client, dest, reason);
}
