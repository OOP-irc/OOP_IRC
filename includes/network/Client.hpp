#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <sys/socket.h>
#include <sys/poll.h>

#include <string>
#include <vector>

class Client;

#include "Channel.hpp"
#include "response.hpp"

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
        void            Send(const std::string& message) const; // 이름 변경
        void            Welcome();

        /* Client Actions */
        void            Join(Channel *channel);
        void            Leave();

        /* Getters */
        int             GetFd() const;
        int             GetPort() const;
        std::string     GetNickname() const;
        std::string     GetUsername() const;
        std::string     GetRealname() const;
        std::string     GetHostname() const;
        std::string     GetRrefix() const;
        eClientState    GetState() const;
        Channel*        GetChannel() const; // 서버에서 옮김

        /* Setters */
        void            SetNickname(const std::string &nickname);
        void            SetUsername(const std::string &username);
        void            SetRealname(const std::string &realname);
        void            SetState(eClientState state);
        void            SetChannel(Channel *channel);

    private:
        Client();
        Client(const Client &src);
        
        void            reply(const std::string& reply); // 캡슐화 이동
            
        int             mFd;
        int             mPort;

        std::string     mNickname;
        std::string     mUsername;
        std::string     mRealname;
        std::string     mHostname;

        eClientState     mState;
        std::map<int, Client *>  mChannels; //// 한 클라이언트 여러채널 최대 10개


};

#endif
