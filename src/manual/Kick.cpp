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
    if (args.size() < 2 || args.size() > 3)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "KICK"));
        return;
    }

    std::string channelName = args[0];
    std::string receiverName = args[1];

    std::string reason = "No reason specified!";


    if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
    {
        reason = "";

        std::vector<std::string>::iterator it = args.begin() + 2;
        std::vector<std::string>::iterator end = args.end();
        reason.append(*it + " ");

        if (reason[0] == ':')
        {
            if (reason[1] == ':')
            {
                reason = reason.substr(2);
            }
            else
            {
                reason = reason.substr(1);
            }
        }

        it++;
        while (it != end)
        {
			reason.append(*it + " ");
            it++;
        }
    }

    Channel *channel = mServer->GetChannel(channelName);

    if (channel == NULL || channel->GetName() != channelName)
    {
        client->SendErrorToClient(Log::GetERRNOTONCHANNEL(client->GetPrefix(), client->GetNickname(), channelName));
        return;
    }

    if (channel->IsOperatorInChannel(client) == false)
    {
        client->SendErrorToClient(Log::GetERRCHANOPRIVSNEEDED(client->GetPrefix(), client->GetNickname(), channelName));
        return;
    }

    Client *receiverClient = mServer->GetClientNickname(receiverName);
    if (receiverClient == NULL)
    {
        client->SendErrorToClient(Log::GetERRNOSUCHNICK(client->GetPrefix(), receiverName, channelName));
        return;
    }

    if (channel->IsClientInChannel(receiverClient) == false) 
    {
        client->SendErrorToClient(Log::GetERRUSERNOTINCHANNEL(client->GetPrefix(), receiverClient->GetNickname(), channelName));
        return;
    }

    if (channel->IsClientInChannel(client) == false)
    {
        client->SendErrorToClient(Log::GetERRUSERNOTINCHANNEL(client->GetPrefix(), client->GetNickname(), channelName));
        return;
    }

    channel->Kick(client, receiverClient, reason);
}
