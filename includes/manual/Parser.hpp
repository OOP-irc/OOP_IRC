
#ifndef IRC_PARSER_HPP
#define IRC_PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>

#include <vector>
#include <map>

class Parser;

#include "Manual.hpp"

class Parser
{
    private:
        Server*                             mServer;
        std::map<std::string, Manual *>    mManuals;
        std::string     trim(const std::string& str);

    public:
        Parser(Server* srv);
        ~Parser();

        void    Invoke(Client* client, const std::string& message);
};

#endif
