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
#include <time.h>
#include <string>

#include <algorithm>
#include <cassert>
#include <vector>
#include <map>
#include <set>

class Server;

#include "Client.hpp"
#include "Channel.hpp"
#include "command/Parser.hpp"

#define MAX_CONNECTIONS 999

class Server
{
    typedef std::vector<pollfd>::iterator		pfd_iterator;
    typedef std::set<Channel *>::iterator		channel_iterator;
    typedef std::map<int, Client *>::iterator	client_iterator;

    public:

        /* Constructor and Destructor */

        Server(const std::string &port, const std::string &password);
        ~Server();

        /* Initialize and Listen */

        void            Start();

        /* Getters */

        Channel*		GetChannel(const std::string &name);
        Client*			GetClient(const std::string &nickname);
        std::string		GetPassword() const;

        // Channel*        create_channel(const std::string &name, const std::string &key, Client *client);

    private:
        int                     mSock;// 소켓통신

        const std::string       mHost;// 사용
        const std::string       mPort;// 사용
        const std::string       mPassword;// 사용

        // mPollfd == PollFileDescriptor
        std::vector<pollfd>     mPollFd;// 사용

        // 클라이언트, 채널 목록(자료구조 변경 가능)
        std::set<Channel *> mChannels;
        std::map<int, Client *> mClients;

        Server();//
        Server(const Server& src);

        // 캡슐화이동
        void            onClientConnect();
        void            onClientDisconnect(int fd);
        void            onClientMessage(int fd);

        /* Handle Clients */
        std::string     readMessage(int fd); // 소켓에서 읽어온 메서지 검증, 

        /* 소켓 생성 */
        int             createSocket();

        /* 추가, 조회, 삭제 */
        //insert()
        //select()
        //delete()

        /* 로그 */
        static void            log(const std::string &message);

};

#endif
