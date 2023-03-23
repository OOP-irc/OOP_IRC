
#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <sys/socket.h>
#include <sys/poll.h>

#include <string>
#include <vector>

class Client;

#include "Channel.hpp"
#include "response.hpp"


enum ClientState
{
    HANDSHAKE,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};

class Client 
{
    private:
        
        int             _fd;
        int             _port;

        std::string     _nickname;
        std::string     _username;
        std::string     _realname;
        std::string     _hostname;

        ClientState     _state;
        Channel*        _channel;


        // 한 클라이언트 여러채널 최대 10개
        // 서버가 업데이트 담당
        std::map<int, Client *>  _channels; 


        Client();
        Client(const Client &src);


        // 캡슐화 이동

        void            reply(const std::string& reply);

    public:

        /* Costructor and Destructor */
        
        Client(int fd, int port, const std::string &hostname);
        ~Client();

        /* Check state */

        bool            is_registered() const;


        /* Send/Recieve Actions */

        void            send(const std::string& message) const; // 이름 변경

        void            welcome();


        /* Client Actions */

        void            join(Channel *channel);
        void            leave();

        /* Getters */

        int             get_fd() const;
        int             get_port() const;

        std::string     get_nickname() const;
        std::string     get_username() const;
        std::string     get_realname() const;
        std::string     get_hostname() const;
        std::string     get_prefix() const;

        Channel*        get_channel() const; // 서버에서 옮김

    
        /* Setters */

        void            set_nickname(const std::string &nickname);
        void            set_username(const std::string &username);
        void            set_realname(const std::string &realname);
        void            set_state(ClientState state);
        void            set_channel(Channel *channel);


};

#endif
