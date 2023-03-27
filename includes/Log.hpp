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


#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " " + channel + " :No such channel"


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
    static std::string GetERRNOTREGISTERED() 
    {
        return "451 :You have not registered";
    }

    /* Numeric Responses */   
    static std::string GetRPLNAMREPLY(const std::string& channelName, const std::string& users) 
    {
        return "353 = " + channelName + " :" + users;
    }

    static std::string GetRPLENDOFNAMES(const std::string& channelName) 
    {
        return "366 " + channelName + " :End of /NAMES list.";
    }

    static std::string GetRPLJOIN(const std::string& clientPrefix, const std::string& channelName)
    {
        return ":" + clientPrefix + " Join :" + "" + channelName;
    }

    /* 사용자가 키(비밀번호)로 채널에 가입하려고 하는데 제공된 키가 올바르지 않을 때   보내는 오류입니다. 사용자가 채널에 참여하려면 올바른 키가 필요합니다. */
    static std::string GetERRBADCHANNELKEY(const std::string& clientPrefix, const std::string& channelName)
    {
        return "475 " + clientPrefix + " " + channelName + " :Cannot join channel (+k)";
    }

    /* 이 오류는 사용자가 최대 사용자 제한(+l 채널 모드로 설정)에 도달한 채널에 가입하려고 할 때 발생합니다. 사용자는 더 많은 사용자를 위한 공간이 생길 때까지 채널에 참여할 수 없습니다 */
    static std::string GetERRCHANNELISFULL(const std::string& clientPrefix, const std::string& channelName)
    {
        return "471 " + clientPrefix + " " + channelName + " :Cannot join channel (+l)";
    }

    /* 이 오류는 사용자가 서버에서 허용한 것보다 더 많은 채널에 참여하려고 할 때 전송됩니다. 사용자는 새 채널에 가입하기 전에 일부 채널을 나가야 합니다. */
    static std::string GetERRTOOMANYCHANNELS(const std::string& clientPrefix, const std::string& channelName)
    {
        return "405 " + clientPrefix + " " + channelName + " :You have joined too many channels";
    }

    /* 이 오류는 사용자가 이미 사용 중이거나 임시로 예약되어 현재 사용할 수 없는 리소스(예: 닉네임 또는 채널 이름)를 사용하려고 할 때 전송됩니다. */
    static std::string GetERRUNAVAILRESOURCE(const std::string& clientPrefix, const std::string& overlappedName)
    {
        return "437 " + overlappedName + " :Nick/channel is temporarily unavailable";
    }
};

#endif