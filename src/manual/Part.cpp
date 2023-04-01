#include "manual/Manual.hpp"

Part::Part(Server* srv) 
    : Manual(srv) 
{
}

Part::~Part() 
{
}

// syntax: PART <channels> [<message>]

void    Part::Execute(Client* client, std::vector<std::string> args)
{
    if (args.empty() || args.size() > 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "PART"));
        return;
    }

    // 채널을 서버에서 받아오거나 생성한다
    std::string name = args[0];
    Channel *channel = mServer->GetChannel(name);
    
    if (channel == NULL)
    {
        client->SendErrorToClient(Log::GetERRNOSUCHCHANNEL(client->GetPrefix(), client->GetNickname(), name));
        return;
    }

    if (channel->IsClientInChannel(client) == false)
    {
        client->SendErrorToClient(Log::GetERRUSERNOTINCHANNEL(client->GetPrefix(), client->GetNickname(), name));
        return;
    }

    channel->Leave(client);
    client->RemoveJoindInChannel(channel);
}
