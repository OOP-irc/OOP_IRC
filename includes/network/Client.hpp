#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <sys/socket.h>
#include <sys/poll.h>

#include <string>
#include <vector>

class Client;

#include "Channel.hpp"
#include "Log.hpp"

enum eClientState
{
    CONNECTED,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};

class Client
{
    public:
        /* Costructor and Destructor */
        Client(int fd, int port, const std::string &hostname);
        ~Client();

        /* Send/Recieve Actions */
        void            SendToClient(const std::string& message, Channel& channel) const;
        void            SendErrorToClient(const std::string& message) const;
        void            HandleClientLoginAndLog();
        void            AddJoindInChannel(Channel *channel);
        void            RemoveJoindInChannel(Channel *channel);
        bool            IsFullJoindInChannlCount();
        void            LeaveAllChannel();

        /* Getters */
        int             GetFd() const;
        int             GetPort() const;
        std::string     GetNickname() const;
        std::string     GetUsername() const;
        std::string     GetRealname() const;
        std::string     GetHostname() const;
        std::string     GetPrefix() const; // 클라이언트에게 메세지 보낼 때 쓰는 접두사
        eClientState    GetState() const;
        int             GetJoindInChannel() const;

        /* Setters */
        void            SetNickname(const std::string &nickname);
        void            SetUsername(const std::string &username);
        void            SetRealname(const std::string &realname);
        void            SetState(eClientState state);

    private:
        Client();
        Client(const Client &src);

        bool            trySend(const std::string& message) const;
        
        int             mFd;
        int             mPort;
        int             mJoinedInChannel;
        const int       MAX_JOINED_IN_CHANNEL;

        std::set<Channel *>      mChannels;

        std::string     mNickname;
        std::string     mUsername;
        std::string     mRealname;
        std::string     mHostname;

        eClientState     mState;
};

#endif
