#include "manual/Manual.hpp"

PrivMsg::PrivMsg(Server* srv)
 : Manual(srv) 
{
}

PrivMsg::~PrivMsg() 
{
}

// syntax: PRIVMSG <msgtarget> :<message>

void    PrivMsg::Execute(Client* client, std::vector<std::string> arr)
{
    if (arr.size() < 2 || arr[0].empty() || arr[1].empty())
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "JOIN"));
        return;
    }

    // extract the target and the message

    std::string channelName = arr.at(0);
    std::string message;

    std::vector<std::string>::iterator it = arr.begin() + 1;
    std::vector<std::string>::iterator end = arr.end();

    // "메세지가 여러 개 일 때 1개로 합친다"
    while (it != end)
    {
        message.append(*it + " ");
        it++;
    }

    // if (message.at(0) == ':')
    //     message = message.substr(1);

    // if notice is for a channel

    if (channelName.at(0) == '#')
    {
        Channel* channel = mServer->GetChannel(channelName.substr(1));

        if (channel == NULL)
        {
            client->SendErrorToClient(Log::GetERRNOSUCHCHANNEL(client->GetNickname(), name));
            return;
        }

        // check if client is in the channel
        if (channel->IsClientInChannel(client) == false)
        {
            client->SendErrorToClient(Log::GetERRNOTONCHANNEL(client->GetPrefix(), channelName));
            return ;
        }

        channel->Broadcast(Log::GetRPLPRIVMSG(client->GetPrefix(), channelName, message));
        return;
    }

    // else if notice is for a client

    // Client  *dest = _srv->get_client(target);
    // if (!dest)
    // {
    //     client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
	// 	return;
    // }

    // dest->write(RPL_PRIVMSG(client->get_prefix(), target, message));
}
