#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#define NDEBUG

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
class Parser;

#include "Client.hpp"
#include "Channel.hpp"
#include "../manual/Parser.hpp"
#include "../Log.hpp"

#define MAX_CONNECTIONS 999

class Server
{
    typedef std::vector<pollfd>::iterator	            	pfd_iterator;
    typedef std::map<std::string, Channel *>::iterator		channel_iterator;
    typedef std::map<int, Client *>::iterator	            client_iterator;

    public:
        /* Constructor and Destructor */
        Server(const std::string &port, const std::string &password);
        ~Server();

        /* Initialize and Listen */
        void            Start();

        /* Getters */
        Channel*		GetChannel(const std::string &name);
        Client*			GetClientNickname(const std::string &nickname);
        std::string		GetPassword() const;

        /* manage channel and client*/
        Channel*        CreateChannel(const std::string &name, const std::string &password, Client *client);
        void            OnClientDisconnect(int fd);

    private:
        int                     mSock;
        const std::string       mHost;
        const std::string       mPort;
        const std::string       mPassword;

        // mPollfd == PollFileDescriptor
        std::vector<pollfd>     mPollFd;

        // 클라이언트, 채널 목록(자료구조 변경 가능)
        std::map<std::string, Channel *> mChannels;
        std::map<int, Client *> mClients;

        Parser *mParser;

        Server();
        Server(const Server& src);

        // 캡슐화이동
        void            onClientConnect();
        void            onClientMessage(int fd);

        /* Handle Clients */
        std::string     readMessage(Client *client, int fd); // 소켓에서 읽어온 메서지 검증
        void            removeClientOnServerAndLog(int fd, Client *client);

        /* 소켓 생성 */
        int             createSocket();

};
#endif

