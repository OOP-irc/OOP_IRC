/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:47:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 15:01:02 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Kick::Kick(Server* server) : Manual(server) {}

Kick::~Kick() {}

// syntax: KICK <channel> <client> :[<message>]

void    Kick::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->Reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "KICK"));
        return;
    }

    std::string name = args[0];
    std::string target = args[1];
    // 클라이언트에게 보낼 이유(reason)
    std::string reason = "No reason specified!";

    // if there is a reason
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

    Channel *channel = client->GetChannel();
    if (!channel || channel->GetName() != name)
    {
        client->Reply(ERR_NOTONCHANNEL(client->GetNickname(), name));
        return;
    }

    if (channel->GetAdmin() != client)
    {
        client->Reply(ERR_CHANOPRIVSNEEDED(client->GetNickname(), name));
        return;
    }

    Client *dest = mServer->GetClient(target);
    if (!dest)
    {
        client->Reply(ERR_NOSUCHNICK(client->GetNickname(), target));
        return;
    }

    if (!dest->GetChannel() || dest->GetChannel() != channel)
    {
        client->Reply(ERR_USERNOTINCHANNEL(client->GetNickname(), dest->GetNickname(), name));
        return;
    }

    // if everything is fine
    channel->Kick(client, dest, reason);
}
