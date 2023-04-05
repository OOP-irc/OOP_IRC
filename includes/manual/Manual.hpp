/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manual.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:46:48 by mikim3            #+#    #+#             */
/*   Updated: 2023/04/05 13:46:58 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_MANUAL_HPP
#define IRC_MANUAL_HPP

#include <numeric>
#include <string>

class Manual;

#include "network/Server.hpp"

//  THE BASE Manual CLASS

class Manual
{
    protected:

        Server* mServer;
        bool    mAuth;

        Manual();
        Manual(const Manual& src);

    public:

        Manual(Server* server, bool auth = true);
        virtual ~Manual();

        bool AuthRequired() const;

        virtual void Execute(Client* client, std::vector<std::string> args) = 0;
};

//  THE Manual CLASSES

class Notice : public Manual
{
    public:

        Notice(Server* server);
        ~Notice();

        void    Execute(Client* client, std::vector<std::string> args);
};

class PrivMsg : public Manual
{
    public:

        PrivMsg(Server* server);
        ~PrivMsg();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Part : public Manual
{
    public:

        Part(Server* server);
        ~Part();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Quit : public Manual
{
    public:

        Quit(Server* server, bool auth);
        ~Quit();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Join : public Manual
{
    public:

        Join(Server* server);
        ~Join();

        void    Execute(Client* client, std::vector<std::string> args);
};

class User : public Manual
{
    public:

        User(Server* serveri, bool auth);
        ~User();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Nick : public Manual
{
    public:

        Nick(Server* server, bool auth);
        ~Nick();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Pass : public Manual
{
    public:

        Pass(Server* server, bool auth);
        ~Pass();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Kick : public Manual
{
    public:

        Kick(Server* server);
        ~Kick();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Ping : public Manual
{
    public:

        Ping(Server* server);
        ~Ping();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Pong : public Manual
{
    public:

        Pong(Server* server);
        ~Pong();

        void    Execute(Client* client, std::vector<std::string> args);
};

class Mode : public Manual
{
    public:

        Mode(Server* server);
        ~Mode();

        void    Execute(Client* client, std::vector<std::string> args);
};

#endif
