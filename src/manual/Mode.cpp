#include "manual/Manual.hpp"

Mode::Mode(Server* server)
    : Manual(server)
{
}

Mode::~Mode()
{
}

// syntax:  MODE <channel> <flags> [<args>]
// o - give/take channel operator privilege;
// k - set/remove the channel key (password);
// l - set/remove the user limit to channel;

void    Mode::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "MODE"));
        return;
    }

    std::string target = args.at(0);

    // 인자로 받은 channel이 존재하는지 확인
    Channel *channel = mServer->GetChannel(target);
    if (!channel)
    {
        client->SendErrorToClient(Log::GetERRNOSUCHCHANNEL(client->GetPrefix(), client->GetNickname(), target));
        return;
    }

    // 명령어를 입력한 클라이언트가 채널의 오퍼레이터가 아니면 오류 반환
    if (!channel->IsOperatorInChannel(client))
    {
        client->SendErrorToClient(Log::GetERRCHANOPRIVSNEEDED(client->GetPrefix(), client->GetNickname(), target));
        return;
    }

	int i = 0;
	char chr;
    bool attach;
    std::string target_name;

    if (args[1].size() > 2)
    {
        attach = true;
    }
    else
    {
        attach = false;
    }

    // o - give/take channel operator privilege;
    // k - set/remove the channel key (password);
    // l - set/remove the user limit to channel;

    // input : /mode #mychat +n mikim2
    // args[0] == "#mychat"
    // args[1] == "+nmikim2" // 붙어서옴
    while ((chr = args[1][i]))
    {
        char prev_c = ((i > 0) ? args[1][i - 1] : '\0');
        int  target_location = (attach ? 1 : 2);

        if (attach)
        {
            target_name = args[target_location].substr(2);
        }
        else
        {
            target_name = args[target_location];
        }
        switch (chr)
        {
            // 오퍼레이터 권한 부여
            // ex : /MODE #mychat +o mikim2 //mikim2를 오퍼레이터로 변경
            //      /MODE #mychat -o mikim2
			case 'o':
            {
                Client *target_client = mServer->GetClientNickname(target_name);

                if (target_client == NULL)
                {
                    client->SendErrorToClient(Log::GetERRUSERNOTINCHANNEL(client->GetPrefix(), client->GetNickname(), channel->GetName()));
                    return ;
                }
                if ((prev_c == '-' || prev_c == '+') && target_name.empty())
                {
                    client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "MODE"));
                    return ;
                }
                else if (prev_c == '-')
                {
                    // 오퍼레이터 인지 확인후 제거
                    if (channel->IsOperatorInChannel(target_client))
                    {
                        channel->DeleteClientOperator(target_client);
                        channel->Broadcast(Log::GetRPLMODE(client->GetPrefix(), channel->GetName(), ("-o"), (target_name)));
                    }
                }
                else if (prev_c == '+')
                {
                    // 오퍼레이터 추가
                    channel->AddClientOperator(target_client);
                    channel->Broadcast(Log::GetRPLMODE(client->GetPrefix(), channel->GetName(), ("+o"), (target_name)));
                }
                break;
            }
            // 채널의 비밀번호설정
            // ex : /MODE #mychat +k 1234
            //      /MODE #mychat +k
            //      /MODE #mychat -k
			case 'k':
            {
                if (prev_c == '+' && target_name.empty())
                {
                    channel->SetSecurityMode(true);
                    channel->Broadcast(Log::GetRPLMODE(client->GetNickname(), channel->GetName(), ("+k"), (target_name)));
                    return ;
                }
                else if (prev_c == '+')
                {
                    channel->SetSecurityMode(true);
                    channel->SetPassword(args[target_location]);
                    channel->Broadcast(Log::GetRPLMODE(client->GetPrefix(), channel->GetName(), ("+k"), (target_name)));
                }
                // 비밀번호 모드를 껐다 키는 멤버변수를 추가할지 고민됨
                else if (prev_c == '-')
                {
                    channel->SetSecurityMode(false);
                    channel->SetPassword("");
                    channel->Broadcast(Log::GetRPLMODE(client->GetPrefix(), channel->GetName(), ("-k"), (target_name)));
                }
                break;
            }
            // 채널내 최대 유저수 설정
            // ex : /MODE #mychat +l 7 // 7명으로 제한
            // ex : /MODE #mychat -l   // 10명으로 제한
			case 'l':
            {
                if (prev_c == '+' && target_name.empty())
                {
                    client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetPrefix(), client->GetNickname(), "MODE"));
                    return;
                }
                else if (prev_c == '+')
                {
                    if ((int)channel->GetClientCount() <= atoi(args[target_location].c_str()))
                    {
                        channel->SetLimit(atoi(args[target_location].c_str()));
                        channel->Broadcast(Log::GetRPLMODE(client->GetPrefix(), channel->GetName(), ("+l"), (target_name)));
                    }
                }
                else if (prev_c == '-')
                {
                    channel->SetLimit(10);
                    channel->Broadcast(Log::GetRPLMODE(client->GetPrefix(), channel->GetName(), ("-l"), (target_name)));
                }
                break;
            }
            default:
                break;
        }
        i++;
    }
}
