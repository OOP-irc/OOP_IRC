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
        //void                        Broadcast(const std::string& message, Client* exclude);
        //void                        AddClient(Client* client);
        //void                        RemoveClient(Client* client);
        void                        Kick(Client* client, Client* target, const std::string& reason);


        /* Getters */
        std::string                 GetName() const;
        Client&                     GetClientOperator() const;
        unsigned int                GetClientCount() const;
        std::string                 GetPassword() const;
        size_t                      GetModeClientLimitCount() const;
        bool                        GetModeN() const;

        //bool                        ExtMsg() const;
        // size_t                      GetSize() const;
        // std::vector<std::string>    GetNicknames();



        /* Setters */
        void                        SetPassword(std::string key);
        void                        SetLimit(size_t clientLimitCount);
        //void                        SetExtMsg(bool flag);
        //                            Set_client(std::vector<Client *>   clients);
    private:
        Channel();
        Channel(const Channel& src);

        std::string             mName;
        Client*                 mClientOperator;
        bool                    mClientCount;
        size_t                  mClientLimitCount;
        const int               MAXIMUM_CLIENT_COUNT;

        std::set<Client *>      mClientsSet;
        std::vector<Client *>   mClientsArray;

        /* Modes */
        std::string             mPassword; // channel key
        size_t                  mModeL; // limit of channel members
        bool                    mModeN; // yes/no external messages    
};

#endif
