#include "network/Client.hpp"

Client::Client(int fd, int port, const std::string &hostname)
    : mFd(fd)
    , mPort(port)
    , mHostname(hostname)
    , mState(CONNECTED)
{
}

Client::~Client()
{
}

void            Client::Send(const std::string& message) const
{
    assert(strlen(message.c_str()) == 0);

    //message에 "\r\n을 추가해야 할 수도 있음"
    if (send(mFd, message.c_str(), strlen(message.c_str()), 0) == -1)
    {
        Log::log("Error Send it client");
        Send(ERR_CANNOTSENDTOCHAN(channel->GetName());
    }
}

/*
    PASS -> NICK -> USER 커맨드완료 후 서버에 등록 상태로 변경 후 로그를 찍어줌
*/
void            Client::HandleClientLoginAndLog()
{
    if (mState != LOGIN || mUsername.empty() || mRealname.empty() || mNickname.empty())
    {

		return;
    }

    
    mState = REGISTERED;
    this->reply(RPL_WELCOME(_nickname));

    char message[100];
    sprintf(message, "%s:%d is now known as %s.", _hostname.c_str(), _port, _nickname.c_str());
    log(message);
}


std::string     Client::GetPrefix() const 
{
    std::string username = mUsername.empty() ? "" : "!" + mUsername;
    std::string hostname = mHostname.empty() ? "" : "@" + mHostname;

    return mNickname + username + hostname;
}