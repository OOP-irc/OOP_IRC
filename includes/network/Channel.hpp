#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

class Channel;

#include <algorithm>

#include "Server.hpp"
#include "Client.hpp"
#include "../Log.hpp"


class Channel 
{
    public:
        /* Constructor and Destructor */
        Channel(const std::string &name, const std::string &key, Client* admin);
        ~Channel();

        /* Channel Actions */
        void                        Join(Client *client, const std::string& password);
        void                        Leave(Client *client);
        void                        Broadcast(const std::string& message);
        void                        Broadcast(const std::string& message, Client *sender);
        //void                        AddClient(Client* client);
        //void                        RemoveClient(Client* client);
        void                        Kick(Client* client, Client* target, const std::string& reason);
        bool                        IsClientInChannel(Client *client);
        void                        AddClientOperator(Client *client);

        /* Getters */
        std::string                 GetName() const;
        unsigned int                GetClientCount() const;
        std::string                 GetPassword() const;
        int                         GetModeClientLimitCount() const;
        // Client*                     GetClientOperator() const;
        // Client*                     GetClientOperator(const std::string nickname) const;
        bool                        IsOperatorInChannel(Client *client) const;

        // bool                        GetModeN() const;

        //bool                        ExtMsg() const;
        // size_t                      GetSize() const;
        // std::vector<std::string>    GetNicknames();


        /* Setters */
        void                        SetPassword(std::string key);
        void                        SetLimit(int clientLimitCount);
        //void                        SetExtMsg(bool flag);
        //                            Set_client(std::vector<Client *>   clients);
    private:
        Channel();
        Channel(const Channel& src);

        std::string             mName;
        Client*                 mClientOperator;// 나중에 없애기
        unsigned int            mClientCount;
        int                     mClientLimitCount;
        const int               MAXIMUM_CLIENT_COUNT;

        std::set<Client *>      mClientsSet;
        std::vector<Client *>   mClientsArray;
        std::set<Client *>      mClientOperatorSet;

        /* Modes */
        std::string             mPassword; // channel key
};

#endif
