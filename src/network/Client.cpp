#include "network/Client.hpp"

Client::Client(int fd, int port, const std::string &hostname)
    : mFd(fd)
    , mPort(port)
    , mJoinedInChannel(0)
    , MAX_JOINED_IN_CHANNEL(4)
    , mNickname("")
    , mUsername("")
    , mRealname("")
    , mHostname(hostname)
    , mSilcedMsg("")
    , mState(CONNECTED)
{
}

Client::~Client()
{
}

void            Client::SendToClient(const std::string& message, Channel& channel) const
{
    if (trySend(message) == false)
    {
        SendErrorToClient(Log::GetERRCANNOTSENDTOCHAN(GetPrefix(), mNickname, channel.GetName()));
    }
}

void            Client::SendErrorToClient(const std::string& message) const
{
    trySend(message);
}

void            Client::TryClientLogin()
{
    if (isReadLogin() == true)
    {
        handleClientLoginAndLog();
    }
}

void            Client::AddJoindInChannel(Channel *channel)
{
    mJoinedInChannel++;
    assert(mJoinedInChannel < MAX_JOINED_IN_CHANNEL);

    mChannels.insert(channel);
}

void            Client::RemoveJoindInChannel(Channel *channel)
{
    mJoinedInChannel--;
    assert(mJoinedInChannel >= 0);

    mChannels.erase(channel);
}

void            Client::LeaveAllChannel()
{
    std::set<Channel *>::iterator channel_iter = mChannels.begin();
    std::set<Channel *>::iterator channel_end = mChannels.end();
    while (channel_iter != channel_end)
    {
        (*channel_iter)->Leave(this);
        channel_iter++;
    }

    mChannels.clear();
    mJoinedInChannel = 0;
}

bool            Client::IsFullJoindInChannlCount()
{
    return mJoinedInChannel < MAX_JOINED_IN_CHANNEL ? false : true;
}

int             Client::GetFd() const
{
    return mFd;
}

int             Client::GetPort() const
{
    return mPort;
}

std::string     Client::GetNickname() const
{
    return mNickname;
}

std::string     Client::GetUsername() const
{
    return mUsername;
}

std::string     Client::GetRealname() const
{
    return mRealname;
}

std::string     Client::GetHostname() const
{
    return mHostname;
}

std::string     Client::GetPrefix() const
{
    return mNickname + "!" + mUsername + "@" + mHostname;
}

std::string     Client::GetSilcedMsg() const
{
    return mSilcedMsg;
}


eClientState    Client::GetState() const
{
    return mState;
}

void            Client::GetChannelListByOther(Client *other, std::vector<Channel *> *list)
{
    std::set<Channel *>::iterator channel_iter = mChannels.begin();
    std::set<Channel *>::iterator channel_end = mChannels.end();
    while (channel_iter != channel_end)
    {
        if ((*channel_iter)->IsClientInChannel(other) == true)
        {
            list->push_back(*channel_iter);
        }

        ++channel_iter;
    }
}

void            Client::SetNickname(const std::string &nickname)
{
    mNickname = nickname;
}

void            Client::SetUsername(const std::string &username)
{
    mUsername = username;
}

void            Client::SetRealname(const std::string &realname)
{
    mRealname = realname;
}

void            Client::SetState(eClientState state)
{
    mState = state;
}

void            Client::SetSilcedMsg(std::string silcedMsg)
{
    mSilcedMsg = silcedMsg;
}


bool            Client::trySend(const std::string& message) const
{
    assert(strlen(message.c_str()) != 0);

    std::string formattedMessage = message + "\r\n";

    if (send(mFd, formattedMessage.c_str(), strlen(formattedMessage.c_str()), 0) == -1)
    {
        ///Log::log("Error Send it client");
        return false;
    }

    return true;
}

/*
    PASS -> NICK -> USER 커맨드완료 후 서버에 등록 상태로 변경 후 로그를 찍어줌
*/

void            Client::handleClientLoginAndLog()
{
    if (isReadLogin() == false)
    {
        trySend(Log::GetERRNOTREGISTERED(GetPrefix(), GetNickname()));
		return;
    }

    mState = REGISTERED;
    trySend(Log::GetRPLWELCOME(GetPrefix(), mNickname));

    ///char buffer[100];
    ///sprintf(buffer, "%s:%d is %s And Login complete.", mHostname.c_str(), mPort, mNickname.c_str());
    ///Log::log(buffer);
}

bool            Client::isReadLogin()
{
    if (mState != LOGIN || mUsername.empty() || mRealname.empty() || mNickname.empty())
    {
        return false;
    }
    return true;
}
