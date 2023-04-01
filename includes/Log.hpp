#ifndef IRC_LOG_HPP
#define IRC_LOG_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>

class Log
{
    public :
        /* Log Response */
        static void log(const std::string& message);

        /* servers to send a welcome message to a client upon a successful connection. */
        static std::string GetRPLWELCOME(const std::string& clientPrefix, const std::string& nickname);
        
        /* lient is not permitted to send messages to a specific channel */
        static std::string GetERRCANNOTSENDTOCHAN(const std::string& clientPrefix, const std::string& nickname, const std::string& channel);

        /* 유저가 아직 등록되지 않았음을 알림 */
        static std::string GetERRNOTREGISTERED(const std::string& clientPrefix, const std::string& nickname);

        /* 사용자가 키(비밀번호)로 채널에 가입하려고 하는데 제공된 키가 올바르지 않을 때   보내는 오류입니다. 사용자가 채널에 참여하려면 올바른 키가 필요합니다. */
        static std::string GetERRBADCHANNELKEY(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName);

        /* 이 오류는 사용자가 최대 사용자 제한(+l 채널 모드로 설정)에 도달한 채널에 가입하려고 할 때 발생합니다. 사용자는 더 많은 사용자를 위한 공간이 생길 때까지 채널에 참여할 수 없습니다 */
        static std::string GetERRCHANNELISFULL(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName);

        /* 이 오류는 사용자가 서버에서 허용한 것보다 더 많은 채널에 참여하려고 할 때 전송됩니다. 사용자는 새 채널에 가입하기 전에 일부 채널을 나가야 합니다. */
        static std::string GetERRTOOMANYCHANNELS(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName);

        /* 이 오류는 사용자가 이미 사용 중이거나 임시로 예약되어 현재 사용할 수 없는 리소스(예: 닉네임 또는 채널 이름)를 사용하려고 할 때 전송됩니다. */
        static std::string GetERRUNAVAILRESOURCE(const std::string& clientPrefix, const std::string& overlappedName);

        /* 채널에 들어온 유저에게 채널 안 유저 목록을 보냄 */
        static std::string GetRPLNAMREPLY(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName, const std::string& messages);
        
        /* 위의 RPLNAMREPLY에서 리스트가 끝났음을 알림 */
        static std::string GetRPLENDOFNAMES(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName);
        
        /* 클라이언트가 채널에 없을 때 */
        static std::string GetERRNOTONCHANNEL(const std::string& clientPrefix, const std::string& nickname, const std::string& channelName);

        /* 커맨드 실행 시 필요한 매개변수가 없을 때 */
        static std::string GetERRNEEDMOREPARAMS(const std::string& clientPrefix, const std::string& clientNickname, const std::string& commandName);

        /* 해당하는 채널이 없을 때 */
        static std::string GetERRNOSUCHCHANNEL(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName);

        /* 해당하는 커맨드가 서버에 없을 때 */
        static std::string GetERRUNKNOWNCOMMAND(const std::string& clientPrefix, const std::string& clientNickname, const std::string& commandName);

        /* 이미 서버에  등록이 되어 있는데 또 등록을 시도 할떄 */
        static std::string GetERRALREADYREGISTRED(const std::string& clientPrefix, const std::string& clientNickname);

        /* 닉네임을 빈킨으로 제출했을때 */
        static std::string GetERRNONICKNAMEGIVEN(const std::string& clientPrefix, const std::string& clientNickname);

        /* 사용중인 닉네임 */
        static std::string GetERRNICKNAMEINUSE(const std::string& clientPrefix, const std::string& clientNickname);

        /* 서버 접속 비밀번호가 틀림 */
        static std::string GetERRPASSWDMISMATCH(const std::string& clientPrefix, const std::string& clientNickname);

        /* 채널 어퍼레이터 권한이 없음 */
        static std::string GetCHANOPRIVSNEEDED(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName);

        static std::string GetERRCHANOPRIVSNEEDED(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName);

        static std::string GetERRNOSUCHNICK(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName);

        static std::string GetERRUSERNOTINCHANNEL(const std::string& clientPrefix, const std::string& clientNickname, const std::string& channelName);

        /* 유저가 채널에 등록했을 때 메세지를 남김 */
        static std::string GetRPLJOIN(const std::string& clientPrefix, const std::string& channelName);

        /* 유저가 떠났을 떄 메세지를 남김*/
        static std::string GetRPLPART(const std::string& clientPrefix, const std::string& channelName);

        /* 서버에게 응답 보낼 때 쓰는 메세지 */
        static std::string GetRPLPRIVMSG(const std::string& clientPrefix, const std::string& channelName, const std::string& message);

        static std::string GetRPLPING(const std::string& clientPrefix, const std::string& token);

        static std::string GetRPLNOTICE(const std::string& clientPrefix, const std::string& channelName, const std::string& message);

        static std::string GetRPLQUIT(const std::string& clientPrefix, const std::string& message);

        static std::string GetRPLKICK(const std::string& clientPrefix, const std::string& channelName, const std::string& clientNickname, const std::string& message);

        static std::string GetRPLMODE(const std::string& clientPrefix, const std::string& channelName, const std::string& modes, const std::string& arguments);
};

#endif