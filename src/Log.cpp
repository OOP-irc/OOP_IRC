#include "Log.hpp"

void Log::log(const std::string &message)
{
    //nix 운영체제가 공식 출시한 1970년 1월 1일 0시 0분 0초를
    //기점으로 현재까지 흐른 시간을 초단위로 나타냅니다.
    time_t timer = time(NULL);
    struct tm* time = localtime(&timer);

    std::cerr << "\033[34m" << time->tm_year + 1900 << "-"
        << std::setw(2) << std::setfill('0') << time->tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << time->tm_mday << " "
        << std::setw(2) << std::setfill('0') << time->tm_hour << ":"
        << std::setw(2) << std::setfill('0') << time->tm_min << ":"
        << std::setw(2) << std::setfill('0') << time->tm_sec << " ";
    
    std::cerr << "\033[31m" << message << "\033[0m" << std::endl;
}

std::string Log::GetRPLWELCOME(const std::string& clientPrefix, const std::string& nickname) 
{
    return ":" + clientPrefix + " " + "001 " + nickname + " :Welcome " + nickname + " to the ft_irc network";
}

std::string Log::GetERRCANNOTSENDTOCHAN(const std::string& clientPrefix, const std::string& nickname, const std::string& channel)
{
    return ":" + clientPrefix + " " + "404 " + nickname + " " + channel + " :Cannot send to channel";
}

std::string Log::GetERRNOTREGISTERED(const std::string& clientPrefix, const std::string& nickname)
{
    return ":" + clientPrefix + " " + "451 " + nickname + " :You have not registered";
}

std::string Log::GetERRBADCHANNELKEY(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "475 " + nickname + " " + channelName + " :Cannot join channel (+k)";
}

std::string Log::GetERRCHANNELISFULL(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "471 " + nickname + " " + channelName + " :Cannot join channel (+l)";
}

std::string Log::GetERRTOOMANYCHANNELS(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "405 " + nickname + " " + channelName + " :You have joined too many channels";
}

std::string Log::GetERRUNAVAILRESOURCE(const std::string& clientPrefix, const std::string& overlappedName)
{
    return ":" + clientPrefix + " " + "437 " + overlappedName + " :Nick/channel is temporarily unavailable";
}

std::string Log::GetRPLNAMREPLY(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName, const std::string& messages) 
{
    return ":" + clientPrefix + " " + "353 " + nickname + " = " + channelName + " :" + messages;
}

std::string Log::GetRPLENDOFNAMES(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName) 
{
    return ":" + clientPrefix + " " + "366 " + nickname + " " + channelName + " :End of /NAMES list.";
}

std::string Log::GetERRNOTONCHANNEL(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "442 " + nickname + " " + channelName + " :You're not on that channel";
}

std::string Log::GetERRNEEDMOREPARAMS(const std::string& clientPrefix, const std::string& clientNickname, const std::string& commandName)
{
    return ":" + clientPrefix + " " + "461 " + clientNickname + " " + commandName + " :Not enough parameters";
}

std::string Log::GetERRNOSUCHCHANNEL(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "403 " + clientNickname + " " + channelName + " :No such channel";
}

std::string Log::GetERRUNKNOWNCOMMAND(const std::string& clientPrefix, const std::string& clientNickname, const std::string& commandName)
{
    return ":" + clientPrefix + " " + "421 " + clientNickname + " " + commandName + " :Unknown command";
}

std::string Log::GetERRALREADYREGISTRED(const std::string& clientPrefix, const std::string& clientNickname)
{
    return ":" + clientPrefix + " " + "462 " + clientNickname + " :You may not register";
}

std::string Log::GetERRNICKNAMEINUSE(const std::string& clientPrefix, const std::string& clientNickname)
{
    return ":" + clientPrefix + " " + "433 " + clientNickname + " " + clientNickname  + " :Nickname is already in use";
}

std::string Log::GetCHANOPRIVSNEEDED(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "482 " + clientNickname + " " + channelName + " :You're not channel operator";
}

std::string Log::GetERRPASSWDMISMATCH(const std::string& clientPrefix, const std::string& clientNickname)
{
    return ":" + clientPrefix + " " + "464 " + clientNickname + " :Password is incorrect";
}

std::string Log::GetERRNONICKNAMEGIVEN(const std::string& clientPrefix, const std::string& clientNickname)
{
    return ":" + clientPrefix + " " + "431 " + clientNickname + " :Nickname not given";
}

std::string Log::GetERRCHANOPRIVSNEEDED(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "482 " + clientNickname + " " + channelName + " :You're not channel operator";
}

std::string Log::GetERRNOSUCHNICK(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "401 " + clientNickname + " " + channelName + " :No such nick/channel";
}

std::string Log::GetERRUSERNOTINCHANNEL(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName)
{
    return ":" + clientPrefix + " " + "441 " + clientNickname + " " + clientNickname + " " + channelName + " :They aren't on that channel";
}

std::string Log::GetRPLJOIN(const std::string& clientPrefix, const std::string& channelName)
{
    return ":" + clientPrefix + " Join :" + "" + channelName;
}

std::string Log::GetRPLPART(const std::string& clientPrefix, const std::string& channelName)
{
    return ":" + clientPrefix + " PART :" + channelName;
}

std::string Log::GetRPLPRIVMSG(const std::string& clientPrefix, const std::string& channelName, const std::string& message)
{
    return ":" + clientPrefix + " PRIVMSG " + channelName + " :" + message;
}

std::string Log::GetRPLPING(const std::string& clientPrefix, const std::string& token)
{
    return ":" + clientPrefix + " PONG :" + token;
}

std::string Log::GetRPLNOTICE(const std::string& clientPrefix, const std::string& channelName, const std::string& message)
{
    return ":" + clientPrefix + " NOTICE " + channelName + " :" + message;
}

std::string Log::GetRPLQUIT(const std::string& clientPrefix, const std::string& message)
{
    return ":" + clientPrefix + " QUIT :Quit: " + message;
}

std::string Log::GetRPLKICK(const std::string& clientPrefix, const std::string& channelName, const std::string& clientNickname, const std::string& message)
{
    return  ":" + clientPrefix + " KICK " + channelName + " " + clientNickname + " :" + message;
}

std::string Log::GetRPLMODE(const std::string& clientPrefix, const std::string& channelName, const std::string& modes, const std::string& arguments)
{
    return  ":" + clientPrefix + " MODE " + channelName + " " + modes + " " + arguments;
}
