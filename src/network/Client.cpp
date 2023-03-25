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

    if (send(mFd, message.c_str(), strlen(message.c_str()), 0) == -1)
    {
        
    }
}