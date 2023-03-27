#include "network/Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client* clientOperator)
    : mName(name)
    , mPassword(password)
    , mClientOperator(clientOperator)
    , MAXIMUM_CLIENT_COUNT(10)
{    
}

int                        Channel::Join(Client *Client)
{
    assert(Client != NULL);
    
    if (Client->GetState() != REGISTERED)
    {
        Client->SendErrorToClient(Log::GetERRNOTREGISTERED());
    }

    //Client를 추가한다
    mClientsArray.push_back(Client);
    mClientsSet.insert(Client);

    //채널에 참여한 클라이언트 이름을 추가한다
    std::string clientsOnChannel = "";

    clientsOnChannel.append(mClientsArray[0]->GetNickname()); 
    for (int i = 1; i < mClientsArray.size(); ++i)
    {
        clientsOnChannel.append(" ");
        clientsOnChannel.append(mClientsArray[i]->GetNickname()); 
    }

    // 클라이언트에 대답을 보낸다
    Client->SendToClient(Log::GetRPLNAMREPLY(mName, clientsOnChannel), *this);
    Client->SendToClient(Log::GetRPLENDOFNAMES(mName), *this);

    channel->broadcast(Log::GetRPLJOIN(Client->GetPrefix(), channel->get_name()));
    log(Client->GetNickname() + " has joined to the channel " + channel->get_name());
}

void                        Channel::Leave()
{

}

// void            Client::leave()
// {
//     if (!_channel)
//         return;

//     const std::string name = _channel->get_name();

//     _channel->broadcast(RPL_PART(get_prefix(), _channel->get_name()));
//     _channel->remove_client(this);

//     std::string message = _nickname + " has left the channel " + name;
//     log(message);
// }

std::string                 Channel::GetName() const
{
    return mName;
}

Client&                     Channel::GetClientOperator() const
{
    return *mClientOperator;
}

unsigned int                Channel::GetClientCount() const
{
    assert(mClientsSet.size() == mClientsArray.size());

    return mClientsArray.size();
}

std::string                 Channel::GetPassword() const
{
    return mPassword;
}

size_t                      Channel::GetModeL() const
{
    return mModeL;
}

bool                        Channel::GetModeN() const
{
    return mModeN;
}