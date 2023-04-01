/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:14:15 by shovsepy          #+#    #+#             */
/*   Updated: 2022/12/30 14:30:19 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Parser.hpp"

Parser::Parser(Server* server) 
    : mServer(server)
{
    mManuals["PASS"] = new Pass(mServer, false);
    mManuals["NICK"] = new Nick(mServer, false);
    mManuals["USER"] = new User(mServer, false);
    mManuals["QUIT"] = new Quit(mServer, false);

    mManuals["PING"] = new Ping(mServer);
    mManuals["PONG"] = new Pong(mServer);
    mManuals["JOIN"] = new Join(mServer);
    mManuals["PART"] = new Part(mServer);
    mManuals["KICK"] = new Kick(mServer);
    mManuals["MODE"] = new Mode(mServer);

	mManuals["PRIVMSG"] = new PrivMsg(mServer);
	mManuals["NOTICE"] = new Notice(mServer);
}

Parser::~Parser ()
{
    std::map<std::string, Manual *>::iterator it = mManuals.begin();
    std::map<std::string, Manual *>::iterator end = mManuals.end();

    while (it != end)
    {
        delete it->second;
        it++;
    }
}


std::string     Parser::trim(const std::string& str)
{
    std::string WHITESPACE = " \n\r\t\f\v";
    std::string result = "";

    size_t  start = str.find_first_not_of(WHITESPACE);
    if (start != std::string::npos)
        result = str.substr(start);

    size_t  end = result.find_last_not_of(WHITESPACE);
    if (end != std::string::npos)
        result = result.substr(0, end + 1);

    return result;
}

void            Parser::Invoke(Client* client, const std::string& message)
{
    std::stringstream   ss(message);
    std::string         syntax;
    
    while (std::getline(ss, syntax))
    {
        syntax = trim(syntax);

        std::string name = syntax.substr(0, syntax.find(' '));

        try
        {
            std::vector<std::string>    args;
            std::stringstream           line(syntax.substr(name.length(), syntax.length()));
            std::string                 buf;

            Manual *manual = mManuals.at(name);

            while (line >> buf)
                args.push_back(buf);

            if (client->GetState() == false && manual->AuthRequired())
            {
                client->SendErrorToClient(Log::GetERRNOTREGISTERED(client->GetPrefix(), client->GetNickname()));
                return;
            }

            manual->Execute(client, args);
        }
        catch (const std::exception& e)
        {
            client->SendErrorToClient(Log::GetERRUNKNOWNCOMMAND(client->GetPrefix(), client->GetNickname(), name));
        }
    }
}
