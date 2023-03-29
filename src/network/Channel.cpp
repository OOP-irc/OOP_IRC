#include "network/Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client* clientOperator)
    : mName(name)
    , mPassword(password)
    , mClientOperator(clientOperator)
    , mClientLimitCount(10)
    , MAXIMUM_CLIENT_COUNT(10)
{    
}

void                        Channel::Join(Client *client, const std::string& password)
{
    assert(client != NULL);
    
    if (client->GetState() != REGISTERED)
    {
        /* 유저가 아직 등록되지 않았음을 알림 */
        client->SendErrorToClient(Log::GetERRNOTREGISTERED());
        return;
    }

    if (!mPassword.empty() && mPassword != password)
    {
        /* 사용자가 키(비밀번호)로 채널에 가입하려고 하는데 제공된 키가 올바르지 않을 때   보내는 오류입니다. 사용자가 채널에 참여하려면 올바른 키가 필요합니다. */
        client->SendErrorToClient(Log::GetERRBADCHANNELKEY(client->GetPrefix(), mName));
        return;
    }

    if (GetClientCount() == GetModeClientLimitCount())
    {
        /* 이 오류는 사용자가 최대 사용자 제한(+l 채널 모드로 설정)에 도달한 채널에 가입하려고 할 때 발생합니다. 사용자는 더 많은 사용자를 위한 공간이 생길 때까지 채널에 참여할 수 없습니다 */
        client->SendErrorToClient(Log::GetERRCHANNELISFULL(client->GetPrefix(), mName));
        return;
    }

    if (client->IsFullJoindInChannlCount() == true)
    {   
        /* 이 오류는 사용자가 서버에서 허용한 것보다 더 많은 채널에 참여하려고 할 때 전송됩니다. 사용자는 새 채널에 가입하기 전에 일부 채널을 나가야 합니다. */
        client->SendErrorToClient(Log::GetERRTOOMANYCHANNELS(client->GetPrefix(), mName));
        return;
    }

    //Client를 Channel에 추가한다
    mClientsArray.push_back(client);
    mClientsSet.insert(client);
    
    //Client의 등록된 채널 수를 증가시킨다
    client->AddJoindInChannel();

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

    // 클라이언트에서 자신이 등록된 채널 수를 줄인다
    client->RemoveJoindInChannel();

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

bool                        Channel::IsClientInChannel(Client *client)
{
    std::set<Client *>::iterator itSet = mClientsSet.find(client);
    if (itSet == mClientsSet.end())
    {
        return false;
    }
    return true;
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

size_t                      Channel::GetModeClientLimitCount() const
{
    return mClientLimitCount;
}

bool                        Channel::GetModeN() const
{
    return mModeN;
}

void                        Channel::SetPassword(std::string key)
{
    mPassword = key;
}

void                        Channel::SetLimit(size_t clientLimitCount)
{
    mClientLimitCount = clientLimitCount > MAXIMUM_CLIENT_COUNT ? MAXIMUM_CLIENT_COUNT : clientLimitCount;
}
