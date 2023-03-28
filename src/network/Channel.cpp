#include "network/Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client* clientOperator)
    : mName(name)
    , mPassword(password)
    , mClientOperator(clientOperator)
    , MAXIMUM_CLIENT_COUNT(10)
{    
}

void                        Channel::Join(Client *client)
{
    assert(client != NULL);
    
    if (client->GetState() != REGISTERED)
    {
        client->SendErrorToClient(Log::GetERRNOTREGISTERED());
        return;
    }


    //Client를 Channel에 추가한다
    mClientsArray.push_back(client);
    mClientsSet.insert(client);


    //채널에 참여한 클라이언트 이름을 추가한다
    std::string clientsOnChannel = "";

    clientsOnChannel.append(mClientsArray[0]->GetNickname()); 
    for (int i = 1; i < mClientsArray.size(); ++i)
    {
        clientsOnChannel.append(" ");
        clientsOnChannel.append(mClientsArray[i]->GetNickname()); 
    }



    // 클라이언트에 대답을 보낸다
    client->SendToClient(Log::GetRPLNAMREPLY(mName, clientsOnChannel), *this);
    client->SendToClient(Log::GetRPLENDOFNAMES(mName), *this);



    // 클라이언트의 채널 참여를 알린다
    Broadcast(Log::GetRPLJOIN(client->GetPrefix(), mName));
    Log::log(client->GetNickname() + " has joined to the channel " + mName);
}

void                        Channel::Leave(Client *client)
{
    assert(GetClientCount != 0);
    assert(client != NULL);

    // 채널에서 클라이언트를 삭제한다
    std::set<Client *>::iterator itSet = mClientsSet.find(client);
    if (itSet == mClientsSet.end())
    {
        /* 클라이언트가 채널에 없을 때 */
        client->SendErrorToClient(Log::GetERRNOTONCHANNEL(client->GetPrefix(), mName));
        return ;
    }
    mClientsSet.erase(itSet);
    
    std::vector<Client *>::iterator itArray = std::find(mClientsArray.begin(), mClientsArray.end(), client);
    assert(itArray != mClientsArray.end());

    mClientsArray.erase(itArray);

    // 떠났음을 채널에 알리고 로그를 찍는다
    Broadcast(Log::GetRPLPART(client->GetPrefix(), mName));
    Log::log(client->GetPrefix() + " has left the channel");
}

void                        Channel::Broadcast(const std::string& message)
{
    for (int i = 0; i < mClientsArray.size(); i++)
    {
        mClientsArray[i]->SendToClient(message, *this);
    }
}

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