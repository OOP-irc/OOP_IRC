#include "network/Client.hpp"

Client::Client(int fd, int port, const std::string &hostname)
    : mFd(fd)
    , mPort(port)
    , mHostname(hostname)
    , mUsername("")
    , mRealname("")
    , mNickname("")
    , mState(CONNECTED)
{
}

Client::~Client()
{
}

Client::Client(const Client &src)
{

}

void            Client::SendToClient(const std::string& message, Channel& channel) const
{
    if (trySend(message) == false)
    {
        SendErrorToClient(Log::GetERRCANNOTSENDTOCHAN(channel.GetName()));
    }
}

void            Client::SendErrorToClient(const std::string& message) const
{
    trySend(message);
}

/*
    PASS -> NICK -> USER 커맨드완료 후 서버에 등록 상태로 변경 후 로그를 찍어줌
*/
void            Client::HandleClientLoginAndLog()
{
    if (mState != LOGIN || mUsername.empty() || mRealname.empty() || mNickname.empty())
    {
        trySend(Log::GetERRNOTREGISTERED());
		return;
    }

    mState = REGISTERED;
    trySend(Log::GetRPLWELCOME(mNickname, mUsername, mHostname));

    char buffer[100];
    sprintf(buffer, "%s:%d is %s And Login complete.", mHostname.c_str(), mPort, mNickname.c_str());
    Log::log(buffer);
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

eClientState    Client::GetState() const
{
    return mState;
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

bool            Client::trySend(const std::string& message) const
{
    assert(strlen(message.c_str()) == 0);

    std::string formattedMessage = message + "\r\n";

    if (send(mFd, formattedMessage.c_str(), strlen(formattedMessage.c_str()), 0) == -1)
    {
        Log::log("Error Send it client");
        
        return false;
    }

    return true;
}