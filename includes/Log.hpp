#ifndef IRC_LOG_HPP
#define IRC_LOG_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>

/* Error Responses */

#define ERR_ALREADYREGISTERED(source)                   "462 " + source + " :You may not register"
#define ERR_PASSWDMISMATCH(source)                      "464 " + source + " :Password is incorrect"
#define ERR_NONICKNAMEGIVEN(source)                     "431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source)                       "433 " + source + " " + source  + " :Nickname is already in use"

#define ERR_UNKNOWNCOMMAND(source, command)             "421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"

#define ERR_TOOMANYCHANNELS(source, channel)            "405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(source, channel)              "471 " + source + " " + channel + " :Cannot join channel (+l)"

#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"

#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"

/* Command Responses */
#define RPL_PART(source, channel)                       ":" + source + " PART :" + channel
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args

class Log
{
public :
    /* Log Response */
    static void log(const std::string& message);

    /* servers to send a welcome message to a client upon a successful connection. */
    static std::string GetRPLWELCOME(const std::string& nickName, const std::string& userName, const std::string& hostName) 
    {
        return "001 Welcome to the Internet Relay Network " + nickName + "!" + userName + "@" + hostName;
    }

    /* lient is not permitted to send messages to a specific channel */
    static std::string GetERRCANNOTSENDTOCHAN(const std::string& channel)
    {
        return "404 " + channel + " :Cannot send to channel";
    }

    /* 유저가 아직 등록되지 않았음을 알림 */
    static std::string GetERR_NOTREGISTERED() 
    {
        return "451 :You have not registered";
    }

    static std::string GetRPL_NAMEREPLY()
    {

    }

    /* Numeric Responses */   
    static std::string GetRPL_NAMREPLY(const std::string& channelName, const std::string& users) 
    {
        return "353 = " + channelName + " :" + users;
    }

    static std::string GetRPL_ENDOFNAMES(const std::string& channelName) 
    {
        return "366 " + channelName + " :End of /NAMES list.";
    }

    static std::string GetRPL_JOIN(const std::string& clientPrefix, const std::string& channelName)
    {
        return ":" + clientPrefix + " Join :" + "" + channelName;
    }
};

#endif