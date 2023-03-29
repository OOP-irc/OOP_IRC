#include "manual/Manual.hpp"

Join::Join(Server* srv)
    : Manual(srv) 
{
}

Join::~Join() 
{
}

// syntax: JOIN <channels> [<keys>]

void    Join::Execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "JOIN"));
        return;
    }

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";


    // 채널을 서버에서 받아오거나 생성한다
    Channel *chan = mServer->GetChannel(name);
    if (chan == NULL)
    {
      chan = mServer->CreateChannel(name, pass, client);
    }

    assert(chan != NULL);
    chan->Join(client, pass);
}
