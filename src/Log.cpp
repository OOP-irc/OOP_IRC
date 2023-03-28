#include "../includes/Log.hpp"

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

static std::string GetRPLWELCOME(const std::string& nickName, const std::string& userName, const std::string& hostName) 
{
    return "001 Welcome to the Internet Relay Network " + nickName + "!" + userName + "@" + hostName;
}

static std::string GetERRCANNOTSENDTOCHAN(const std::string& channel)
{
    return "404 " + channel + " :Cannot send to channel";
}

static std::string GetERRNOTREGISTERED() 
{
    return "451 :You have not registered";
}

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

static std::string GetERRBADCHANNELKEY(const std::string& clientPrefix, const std::string& channelName)
{
    return "475 " + clientPrefix + " " + channelName + " :Cannot join channel (+k)";
}

static std::string GetERRCHANNELISFULL(const std::string& clientPrefix, const std::string& channelName)
{
    return "471 " + clientPrefix + " " + channelName + " :Cannot join channel (+l)";
}

static std::string GetERRTOOMANYCHANNELS(const std::string& clientPrefix, const std::string& channelName)
{
    return "405 " + clientPrefix + " " + channelName + " :You have joined too many channels";
}

static std::string GetERRUNAVAILRESOURCE(const std::string& clientPrefix, const std::string& overlappedName)
{
    return "437 " + overlappedName + " :Nick/channel is temporarily unavailable";
}