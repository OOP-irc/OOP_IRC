
#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

class Channel;

#include "Server.hpp"
#include "Client.hpp"

#include "../response.hpp"

class Channel 
{
    typedef std::vector<Client *>::iterator client_iterator;

    private:

        std::string             mName;
        Client*                 mAdmin;
        std::vector<Client *>   mClients;

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

        void                        Add_client(Client* client);
        void                        Remove_client(Client* client);

        void                        Kick(Client* client, Client* target, const std::string& reason);


        /* Getters */

        std::string                 Get_name() const;
        Client*                     Get_admin() const;
        
        std::string                 Get_key() const;
        size_t                      Get_limit() const;
        bool                        Ext_msg() const;

        size_t                      Get_size() const;
        std::vector<std::string>    Get_nicknames();


        /* Setters */

        void                        Set_key(std::string key);
        void                        Set_limit(size_t limit);
        void                        Set_ext_msg(bool flag);
        //                          Set_client(std::vector<Client *>   clients);
};

#endif
