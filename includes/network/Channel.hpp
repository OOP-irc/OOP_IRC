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
        void                        Kick(Client* client, Client* receiver, const std::string& reason);
        bool                        IsClientInChannel(Client *client);
        void                        AddClientOperator(Client *client);
        void                        DeleteClientOperator(Client *client);

        /* Getters */
        std::string                 GetName() const;
        unsigned int                GetClientCount() const;
        std::string                 GetPassword() const;
        int                         GetModeClientLimitCount() const;
        bool                        IsOperatorInChannel(Client *client) const;


        /* Setters */
        void                        SetPassword(std::string key);
        void                        SetLimit(int clientLimitCount);
        void                        SetSecurityMode(bool SecurityMode);

    private:
        Channel();
        Channel(const Channel& src);

        std::string             mName;
        int                     mClientLimitCount;
        const int               MAXIMUM_CLIENT_COUNT;

        std::set<Client *>      mClientsSet;
        std::vector<Client *>   mClientsArray;
        std::set<Client *>      mClientOperatorSet;

        /* Modes */
        std::string             mPassword; // channel key
        bool                    mSecurityMode; // 비밀번호로 채널이 잠겼는지 체크
};

#endif
