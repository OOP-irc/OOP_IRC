#include "network/Channel.hpp"

Channel::Channel(const std::string &name, const std::string &password, Client* clientOperator)
    : mName(name)
    , mClientLimitCount(3)
    , MAXIMUM_CLIENT_COUNT(3)
    , mPassword(password)
    , mSecurityMode(false)
{
    mClientOperatorSet.insert(clientOperator);
}

Channel::~Channel()
{
}

void                        Channel::Join(Client *client, const std::string& password)
{
    assert(client != NULL);

    if (client->GetState() != REGISTERED)
    {
        /* 유저가 아직 등록되지 않았음을 알림 */
        client->SendErrorToClient(Log::GetERRNOTREGISTERED(client->GetPrefix(), client->GetNickname()));
        return;
    }

    if (IsClientInChannel(client))
    {
        /* 클라이언트가 자신이 있는 채널에 들어오려고 함 */
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "JOIN"));
        return;
    }

    if (mSecurityMode && !mPassword.empty() && mPassword != password)
    {
        /* 사용자가 키(비밀번호)로 채널에 가입하려고 하는데 제공된 키가 올바르지 않을 때   보내는 오류입니다. 사용자가 채널에 참여하려면 올바른 키가 필요합니다. */
        client->SendErrorToClient(Log::GetERRBADCHANNELKEY(client->GetPrefix(), client->GetNickname(), mName));
        return;
    }

    if (GetClientCount() >= (unsigned int)GetModeClientLimitCount())
    {
        /* 이 오류는 사용자가 최대 사용자 제한(+l 채널 모드로 설정)에 도달한 채널에 가입하려고 할 때 발생합니다. 사용자는 더 많은 사용자를 위한 공간이 생길 때까지 채널에 참여할 수 없습니다 */
        client->SendErrorToClient(Log::GetERRCHANNELISFULL(client->GetPrefix(), client->GetNickname(), mName));
        return;
    }

    if (client->IsFullJoindInChannlCount() == true)
    {
        /* 이 오류는 사용자가 서버에서 허용한 것보다 더 많은 채널에 참여하려고 할 때 전송됩니다. 사용자는 새 채널에 가입하기 전에 일부 채널을 나가야 합니다. */
        client->SendErrorToClient(Log::GetERRTOOMANYCHANNELS(client->GetPrefix(), client->GetNickname(), mName));
        return;
    }

    //Client를 Channel에 추가한다
    mClientsArray.push_back(client);
    mClientsSet.insert(client);

    //Client의 등록된 채널을 증가시킨다
    client->AddJoindInChannel(this);

    //채널에 참여한 클라이언트 이름을 추가한다
    std::string clientsOnChannel = "";

    clientsOnChannel.append(mClientsArray[0]->GetNickname());
    for (size_t i = 1; i < mClientsArray.size(); ++i)
    {
        clientsOnChannel.append(" ");
        clientsOnChannel.append(mClientsArray[i]->GetNickname());
    }

    // 클라이언트에 대답을 보낸다
    client->SendToClient(Log::GetRPLNAMREPLY(client->GetPrefix(), client->GetNickname(), mName, clientsOnChannel), *this);
    client->SendToClient(Log::GetRPLENDOFNAMES(client->GetPrefix(), client->GetNickname(), mName), *this);

    // 클라이언트의 채널 참여를 알린다
    Broadcast(Log::GetRPLJOIN(client->GetPrefix(), mName));
    ///Log::log(client->GetNickname() + " has joined to the channel " + mName);
}

void                        Channel::Leave(Client *client)
{
    assert(GetClientCount() != 0);
    assert(client != NULL);

    // 떠났음을 채널에 알리고 로그를 찍는다
    Broadcast(Log::GetRPLPART(client->GetPrefix(), mName));
    ///Log::log(client->GetPrefix() + " has left the channel");


    // 채널에서 클라이언트를 삭제한다
    std::set<Client *>::iterator itSet = mClientsSet.find(client);
    if (itSet == mClientsSet.end())
    {
        /* 클라이언트가 채널에 없을 때 */
        client->SendErrorToClient(Log::GetERRNOTONCHANNEL(client->GetPrefix(), client->GetNickname(), mName));
        return ;
    }
    mClientsSet.erase(itSet);

    std::vector<Client *>::iterator itArray = std::find(mClientsArray.begin(), mClientsArray.end(), client);
    assert(itArray != mClientsArray.end());

    mClientsArray.erase(itArray);
}

void                        Channel::Broadcast(const std::string& message)
{
    for (size_t i = 0; i < mClientsArray.size(); ++i)
    {
        mClientsArray[i]->SendToClient(message, *this);
    }
}

void                        Channel::Broadcast(const std::string& message, Client *sender)
{
    ///std::cout << message << std::endl;
    for (size_t i = 0; i < mClientsArray.size(); ++i)
    {
        if (mClientsArray[i] != sender)
        {
            mClientsArray[i]->SendToClient(message, *this);
        }
    }
}

void                        Channel::Kick(Client* client, Client* receiver, const std::string& reason)
{
    Broadcast(Log::GetRPLKICK(client->GetPrefix(), mName, receiver->GetNickname(), reason));

    // 채널에서 클라이언트를 삭제한다
    std::set<Client *>::iterator itSet = mClientsSet.find(receiver);
    if (itSet == mClientsSet.end())
    {
        /* 클라이언트가 채널에 없을 때 */
        receiver->SendErrorToClient(Log::GetERRNOTONCHANNEL(receiver->GetPrefix(), receiver->GetNickname(), mName));
        return ;
    }
    mClientsSet.erase(itSet);

    std::vector<Client *>::iterator itArray = std::find(mClientsArray.begin(), mClientsArray.end(), receiver);
    assert(itArray != mClientsArray.end());

    mClientsArray.erase(itArray);

    // 클라이언트에서 자신이 등록된 채널을 줄인다
    receiver->RemoveJoindInChannel(this);

    ///Log::log(client->GetNickname() + " kicked " + receiver->GetNickname() + " from channel " + mName);
}

void                        Channel::AddClientOperator(Client *client)
{
    assert(client != NULL);

    // Client가 이 채널에 속해 있는지 확인한다.
    if (!IsClientInChannel(client))
    {
        return ;
    }

    //Client를 Operator에 추가한다
    mClientOperatorSet.insert(client);

}

void                        Channel::DeleteClientOperator(Client *client)
{
    assert(client != NULL);

    // Client가 이 채널에 속해 있는지 확인한다.
    if (!IsClientInChannel(client))
    {
        return ;
    }

    // Set 목록에서 제거
    mClientOperatorSet.erase(client);
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

bool                        Channel::IsOperatorInChannel(Client *client) const
{
    std::set<Client *>::iterator itSet = mClientOperatorSet.find(client);
    if (itSet == mClientOperatorSet.end())
    {
        return false;
    }
    return true;
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

int                      Channel::GetModeClientLimitCount() const
{
    return mClientLimitCount;
}

void                        Channel::SetPassword(std::string key)
{
    mPassword = key;
}

void                        Channel::SetLimit(int clientLimitCount)
{
    mClientLimitCount = clientLimitCount > MAXIMUM_CLIENT_COUNT ? MAXIMUM_CLIENT_COUNT : clientLimitCount;
}

void                        Channel::SetSecurityMode(bool SecurityMode)
{
    mSecurityMode = SecurityMode;
}
