#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdexcept>
#include <cerrno>
#include <string>

#include <algorithm>
#include <vector>
#include <map>

class Server;

#include "Client.hpp"
#include "Channel.hpp"
#include "command/Parser.hpp"

#define MAX_CONNECTIONS 999

class Server
{
    typedef std::vector<pollfd>::iterator       pfd_iterator;
    typedef std::vector<Channel *>::iterator    channel_iterator;
    typedef std::map<int, Client *>::iterator   client_iterator;

    private:
<<<<<<< HEAD
        
        // int                     _running; //폐기
        int                     _sock;// 서버의 소켓 파일 디스크립터를 나타내는 정수
=======
        int                     mSock;// 소켓통신
>>>>>>> 226262828387b3b19a3faa676da3f8ee50620fee

        const std::string       mHost;// 사용
        const std::string       mPort;// 사용
        const std::string       mPassword;// 사용

<<<<<<< HEAD
        std::vector<pollfd>     _pfds;// 모니터링할 파일 디스크립터를 나타내는 pollfd 구조체의 벡터
=======
        // mPollfd == PollFileDescriptor
        std::vector<pollfd>     mPollFd;// 사용
>>>>>>> 226262828387b3b19a3faa676da3f8ee50620fee


        // 클라이언트, 채널 목록(자료구조 변경 가능)
        // std::set<Channel *> _channels;
        std::map<int, Client *> mClients; 

        // 채널들에 속해 있는 클라이언트들의 목록(자료구조 변경가능)
        // std::map<Channel*, std::set<Client *>  _channels;

        Server();// 
        Server(const Server& src);

        // 캡슐화이동
        void            on_client_connect();
        void            on_client_disconnect(int fd);
        void            on_client_message(int fd);

        /* Handle Clients */
        std::string     read_message(int fd); // 소켓에서 읽어온 메서지 검증, 

        /* 소켓 생성 */
        int             create_socket();

        /* 추가, 조회, 삭제 */
        //insert()
        //select()
        //delete()

    public:

        /* Constructor and Destructor */

        Server(const std::string &port, const std::string &password);
        ~Server();

        /* Initialize and Listen */

        void            start();

        /* Getters */

        std::string     get_password() const;
        Client*         get_client(const std::string &nickname);
        // Channel*        get_channel(const std::string &name);

        //채널 Getter

        //클라이언트 Getter


        /* Create Channel */

        // Channel*        create_channel(const std::string &name, const std::string &key, Client *client);
};

#endif
