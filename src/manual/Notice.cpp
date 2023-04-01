#include "manual/Manual.hpp"

Notice::Notice(Server* srv)
 : Manual(srv) 
{
}

Notice::~Notice() 
{
}

// syntax: PRIVMSG <msgtarget> <text>

void    Notice::Execute(Client* client, std::vector<std::string> arr)
{
    if (arr.size() < 2 || arr[0].empty() || arr[1].empty())
    {
        Log::log((Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "JOIN")));
        return;
    }

    // extract the target and the message

    std::string recieverName = arr.at(0);
    std::string message;

    std::vector<std::string>::iterator it = arr.begin() + 1;
    std::vector<std::string>::iterator end = arr.end();

    // "메세지가 여러 개 일 때 1개로 합친다"
    while (it != end)
    {
        message.append(*it + " ");
        it++;
    }

    // if notice is for a channel

    if (recieverName.at(0) == '#')
    {
        Channel* channel = mServer->GetChannel(recieverName);

        if (channel == NULL)
        {
            Log::log(Log::GetERRNOSUCHCHANNEL(client->GetPrefix(), client->GetNickname(), recieverName));
            return;
        }

        // check if client is in the channel
        if (channel->IsClientInChannel(client) == false)
        {
            Log::log((Log::GetERRNOTONCHANNEL(client->GetPrefix(), client->GetNickname(), recieverName)));
            return ;
        }

        channel->Broadcast(Log::GetRPLNOTICE(client->GetNickname(), recieverName, message), client);
        return;
    }
    else
    {
        Client *receivedClient = mServer->GetClientNickname(recieverName);

        if (receivedClient == NULL)
        {
            Log::log(Log::GetERRNOSUCHNICK(client->GetPrefix(), client->GetNickname(), recieverName));
            return;
        }

        //클라이언트a와 다른 클라이언트 b가 속한 채널을 알아낸다
        // 클라이언트 에이에 대한 채널을 가져온다
        // 클라이언트 비에 대한 채널을 가져온다
        // 서로 비교 후 새로운 채널리스트를 가져온다
        std::vector<Channel *> *list = new std::vector<Channel *>();
        receivedClient->GetChannelListByOther(client, list);

        if (list->size() == 0)
        {
            Log::log((Log::GetERRNOTONCHANNEL(client->GetPrefix(), client->GetNickname(), recieverName)));
            delete list;
            return ;
        }

        for (size_t i = 0; i < list->size(); ++i)
        {
            receivedClient->SendToClient(Log::GetRPLNOTICE(client->GetNickname(), list->at(i)->GetName(), message), *(list->at(i)));
        }

        delete list;
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
