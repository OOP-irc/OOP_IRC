/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manual.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:46:48 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/25 17:04:22 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_MANUAL_HPP
#define IRC_MANUAL_HPP

#include <numeric>
#include <string>

class Manual;

#include "network/Server.hpp"

//==========================
//  THE BASE Manual CLASS
//==========================  

class Manual
{
    protected:

        Server* mServer;
        bool    mAuth;

        Manual();
        Manual(const Manual& src);

    public:

        explicit Manual(Server* srv, bool auth = true);
        virtual ~Manual();

        bool auth_required() const;

        virtual void execute(Client* client, std::vector<std::string> args) = 0;
};


//=======================
//  THE Manual CLASSES
//=======================

class Notice : public Manual
{
    public:

        Notice(Server* srv);
        ~Notice();

        void    execute(Client* client, std::vector<std::string> args);
};

class PrivMsg : public Manual
{
    public:

        PrivMsg(Server* srv);
        ~PrivMsg();

        void    execute(Client* client, std::vector<std::string> args);
};

class Part : public Manual
{
    public:

        Part(Server* srv);
        ~Part();

        void    execute(Client* client, std::vector<std::string> args);
};

class Quit : public Manual
{
    public:

        Quit(Server* srv, bool auth);
        ~Quit();

        void    execute(Client* client, std::vector<std::string> args);
};

class Join : public Manual
{
    public:

        Join(Server* srv);
        ~Join();

        void    execute(Client* client, std::vector<std::string> args);
};

class User : public Manual
{
    public:

        User(Server* srvi, bool auth);
        ~User();

        void    execute(Client* client, std::vector<std::string> args);
};

class Nick : public Manual
{
    public:

        Nick(Server* srv, bool auth);
        ~Nick();

        void    execute(Client* client, std::vector<std::string> args);
};

class Pass : public Manual
{
    public:

        Pass(Server* srv, bool auth);
        ~Pass();

        void    execute(Client* client, std::vector<std::string> args);
};

class Kick : public Manual
{
    public:

        Kick(Server* srv);
        ~Kick();

        void    execute(Client* client, std::vector<std::string> args);
};

class Ping : public Manual
{
    public:

        Ping(Server* srv);
        ~Ping();

        void    execute(Client* client, std::vector<std::string> args);
};

class Pong : public Manual
{
    public:

        Pong(Server* srv);
        ~Pong();

        void    execute(Client* client, std::vector<std::string> args);
};

class Mode : public Manual
{
    public:

        Mode(Server* srv);
        ~Mode();

        void    execute(Client* client, std::vector<std::string> args);
};

#endif
