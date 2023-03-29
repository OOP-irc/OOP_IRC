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

std::string Log::GetRPLWELCOME(const std::string& nickName, const std::string& userName, const std::string& hostName) 
{
    return "001 Welcome to the Internet Relay Network " + nickName + "!" + userName + "@" + hostName;
}

std::string Log::GetERRCANNOTSENDTOCHAN(const std::string& channel)
{
    return "404 " + channel + " :Cannot send to channel";
}

std::string Log::GetERRNOTREGISTERED() 
{
    return "451 :You have not registered";
}

std::string Log::GetRPLNAMREPLY(const std::string& channelName, const std::string& users) 
{
    return "353 = " + channelName + " :" + users;
}

std::string Log::GetRPLENDOFNAMES(const std::string& channelName) 
{
    return "366 " + channelName + " :End of /NAMES list.";
}

std::string Log::GetRPLJOIN(const std::string& clientPrefix, const std::string& channelName)
{
    return ":" + clientPrefix + " Join :" + "" + channelName;
}

std::string Log::GetERRBADCHANNELKEY(const std::string& clientPrefix, const std::string& channelName)
{
    return "475 " + clientPrefix + " " + channelName + " :Cannot join channel (+k)";
}

std::string Log::GetERRCHANNELISFULL(const std::string& clientPrefix, const std::string& channelName)
{
    return "471 " + clientPrefix + " " + channelName + " :Cannot join channel (+l)";
}

std::string Log::GetERRTOOMANYCHANNELS(const std::string& clientPrefix, const std::string& channelName)
{
    return "405 " + clientPrefix + " " + channelName + " :You have joined too many channels";
}

std::string Log::GetERRUNAVAILRESOURCE(const std::string& overlappedName)
{
    return "437 " + overlappedName + " :Nick/channel is temporarily unavailable";
}

std::string Log::GetERRNOTONCHANNEL(const std::string& clientPrefix, const std::string& channelName)
{
    return "442 " + clientPrefix + " " + channelName + " :You're not on that channel";
}

std::string Log::GetRPLPART(const std::string& clientPrefix, const std::string& channelName)
{
    return ":" + clientPrefix + " PART :" + channelName;
}

std::string Log::GetERRNEEDMOREPARAMS(const std::string& clientNickname, const std::string& commandName)
{
    return "461 " + clientNickname + " " + commandName + " :Not enough parameters";
}

std::string Log::GetERRNOSUCHCHANNEL(const std::string& clientPrefix, const std::string& channelName)
{
    return "403 " + clientPrefix + " " + channelName + " :No such channel";
}

std::string Log::GetRPLPRIVMSG(const std::string& clientPrefix, const std::string& channelName, const std::string& message)
{
    return ":" + clientPrefix + " PRIVMSG " + channelName + " :" + message;
}

std::string Log::GetERRUNKNOWNCOMMAND(const std::string& clientNickname, const std::string& commandName)
{
    return "421 " + clientNickname + " " + commandName + " :Unknown command";
}

std::string Log::GetERRALREADYREGISTRED(const std::string& clientPrefix)
{
    return "462 " + clientPrefix + " :Unauthorized command (already registered)";
}

std::string Log::GetERRNONICKNAMEGIVEN(const std::string& clientPrefix)
{
    return "431 " + clientPrefix + " :Nickname not given";
}

std::string Log::GetERRNICKNAMEINUSE(const std::string& clientPrefix)
{
    return "433 " + clientPrefix + " " + clientPrefix  + " :Nickname is already in use";
}

std::string Log::GetERRPASSWDMISMATCH(const std::string& clientPrefix)
{
    return "464 " + clientPrefix + " :Password is incorrect";
}
