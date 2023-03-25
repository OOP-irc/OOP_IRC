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