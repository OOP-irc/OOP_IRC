
#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

class Channel;

#include "Server.hpp"
#include "Client.hpp"

#include "../Log.hpp"

class Channel 
{
    typedef std::vector<Client *>::iterator client_iterator;

    private:

        std::string             mName;
        Client*                 mAdmin;
        std::set<Client *>      mClientsSet;
        std::vector<Client *>   mClientsArray;

        /* Modes */
        std::string             mModeK; // channel key
        size_t                  mModeL; // limit of channel members
        bool                    mModeN; // yes/no external messages

        Channel();
        Channel(const Channel& src);
    
    public:

        /* Constructor and Destructor */

        Channel(const std::string &name, const std::string &key, Client* admin);
        ~Channel();


        /* Channel Actions */

        void                        Broadcast(const std::string& message);
        void                        Broadcast(const std::string& message, Client* exclude);

        void                        AddClient(Client* client);
        void                        RemoveClient(Client* client);

        void                        Kick(Client* client, Client* target, const std::string& reason);


        /* Getters */

        std::string                 GetName() const;
        Client*                     GetAdmin() const;
        
        std::string                 GetKey() const;
        size_t                      GetLimit() const;
        bool                        ExtMsg() const;

        size_t                      GetSize() const;
        std::vector<std::string>    GetNicknames();


        /* Setters */

        void                        SetKey(std::string key);
        void                        SetLimit(size_t limit);
        void                        SetExtMsg(bool flag);
        //                          Set_client(std::vector<Client *>   clients);
};

#endif
