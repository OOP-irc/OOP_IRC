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
    private:
        
        int             mFd;
        int             mPort;

        std::string     mNickname;
        std::string     mUsername;
        std::string     mRealname;
        std::string     mHostname;

        eClientState     mState;
        Channel*        mChannel;


        // 한 클라이언트 여러채널 최대 10개
        // 서버가 업데이트 담당
        std::map<int, Client *>  mChannels; 


        Client();
        Client(const Client &src);


        // 캡슐화 이동

        void            reply(const std::string& reply);

    public:

        /* Costructor and Destructor */
        
        Client(int fd, int port, const std::string &hostname);
        ~Client();

        /* Check state */

        bool            Is_registered() const;


        /* Send/Recieve Actions */

        void            Send(const std::string& message) const; // 이름 변경

        void            Welcome();


        /* Client Actions */

        void            Join(Channel *channel);
        void            Leave();

        /* Getters */

        int             Get_fd() const;
        int             Get_port() const;

        std::string     Get_nickname() const;
        std::string     Get_username() const;
        std::string     Get_realname() const;
        std::string     Get_hostname() const;
        std::string     Get_prefix() const;

        Channel*        Get_channel() const; // 서버에서 옮김

    
        /* Setters */

        void            Set_nickname(const std::string &nickname);
        void            Set_username(const std::string &username);
        void            Set_realname(const std::string &realname);
        void            Set_state(eClientState state);
        void            Set_channel(Channel *channel);
};

#endif
