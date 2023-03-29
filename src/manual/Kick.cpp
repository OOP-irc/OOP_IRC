/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:47:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 17:24:03 by mikim3           ###   ########.fr       */
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
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "KICK"));
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

    // GetJoindInChannel 아직 미구현 
    Channel *channel = client->GetJoindInChannel();

    // 명령을 입력한 본인이 채널에 속해있는지 확인 ERR_NOTONCHANNEL
    if (!channel || channel->GetName() != name)
    {
        client->SendErrorToClient(ERR_NOTONCHANNEL(client->GetNickname(), name));
        return;
    }

    // if (channel->GetAdmin() != client)
    // {
    //     client->SendErrorToClient(ERR_CHANOPRIVSNEEDED(client->GetNickname(), name));
    //     return;
    // }
    
    // client를 client->GetClient()          GetClient() {  return (this*);}
    if (channel->GetClientOperator() != client->GetClient())
    {
        client->SendErrorToClient(ERR_CHANOPRIVSNEEDED(client->GetNickname(), name));
        return;
    }

    Client *targetClient = mServer->GetClient(target);

    // 서버 안에 일치하는 클라이언트가 없음  
    if (!targetClient)
    {
        client->SendErrorToClient(ERR_NOSUCHNICK(client->GetNickname(), target));
        return;
    }

    if (!targetClient->GetJoindInChannel() || targetClient->GetJoindInChannel() != channel)
    {
        client->SendErrorToClient(ERR_USERNOTINCHANNEL(client->GetNickname(), targetClient->GetNickname(), name));
        return;
    }

    channel->Kick(client, targetClient, reason);
}
