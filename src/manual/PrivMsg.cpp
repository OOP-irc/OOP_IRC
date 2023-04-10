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
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "PRIVMSG"));
        return;
    }

    // extract the target and the message

    std::string channelName = arr.at(0);
    std::string message;

    std::vector<std::string>::iterator it = arr.begin() + 1;
    std::vector<std::string>::iterator end = arr.end();

    // "메세지가 여러 개 일 때 1개로 합친다"
    message.append(*it + " ");
    if (message[0] == ':')
        message = message.substr(1);
    it++;
    while (it != end)
    {
        message.append(*it + " ");
        it++;
    }

    // if notice is for a channel

    if (channelName.at(0) == '#')
    {
        Channel* channel = mServer->GetChannel(channelName);

        if (channel == NULL)
        {
            client->SendErrorToClient(Log::GetERRNOSUCHCHANNEL(client->GetPrefix(), client->GetNickname(), channelName));
            return;
        }

        // check if client is in the channel
        if (channel->IsClientInChannel(client) == false)
        {
            client->SendErrorToClient(Log::GetERRNOTONCHANNEL(client->GetPrefix(), client->GetNickname(), channelName));
            return ;
        }

        channel->Broadcast(Log::GetRPLPRIVMSG(client->GetPrefix(), channelName, message), client);
        return;
    }
}
