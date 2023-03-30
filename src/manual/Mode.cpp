#include "manual/Manual.hpp"

Mode::Mode(Server* server)
    : Manual(server) 
{
}

Mode::~Mode() 
{
}

// syntax:  MODE <nickname> <flags> (user)
//          MODE <channel> <flags> [<args>]
// o - give/take channel operator privilege;
// k - set/remove the channel key (password);
// l - set/remove the user limit to channel;
// b - set/remove ban mask to keep users out;
// e - set/remove an exception mask to override a ban mask;
// ex:      MODE #Finnish +o Kilroy // #Finnish 채널에서 Kilroy에게 'chanop'권한을 부여합니다.
//  

void    Mode::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "KICK"));
        return;
    }
    
    std::string target = args.at(0);
    
    //MODE on clients not implemented
    Channel *channel = mServer->GetChannel(target); 
    if (!channel)
    {
        client->SendErrorToClient(Log::GetERRNOSUCHCHANNEL(client->GetPrefix(), client->GetNickname(), target));
        return;
    }

    // if (channel->get_admin() != client)
    // {
    //     client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), target));
    //     return;
    // }

    // // changing the mode

	int i = 0; 
    int present = 2;
	char chr;

    // o - give/take channel operator privilege;
    // k - set/remove the channel key (password);
    // l - set/remove the user limit to channel;

    // args[0] == "#mychat"
    // args[1] == "+n"

    // while ((chr = args[1][i]))
    // {
    //     char prev_c = ((i > 0) ? args[1][i - 1] : '\0');
    //     bool active = (prev_c == '+');

    //     switch (chr)
    //     {
    //         // 오퍼레이터 권한 부여
    //         // ex : /MODE #mychat +o mikim2 //mikim2를 오퍼레이터로 변경
    //         //      /MODE #mychat -o mikim2
	// 		case 'o':
    //         {
    //             if (prev_c == '-')
    //             {

    //             }
    //             else if (prev_c == '+')
    //             {
    //                 channel->AddClientOperator(active ? (args[2]) : "");
    //                 channel->Broadcast(RPL_MODE(client->GetPrefix(), channel->GetName(), (active ? "+o" : "-o"), (active ? args[2] : "")));
    //             }
    //             break;
    //         }
    //         // 채널의 비밀번호설정
    //         // ex : /MODE #mychat +k 1234
    //         //      /MODE #mychat -k
	// 		case 'k':
    //         {   
    //             // +인데 3번째 인자 비어있음
    //             if (active && args[2].empty())
    //             {
    //                 client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "MODE"));
    //                 return;
    //             }
    //             channel->SetPassword(active ? args[present] : "");
    //             channel->Broadcast(RPL_MODE(client->GetPrefix(), channel->GetName(), (active ? "+k" : "-k"), (active ? args[present] : "")));
    //             break;
    //         }
    //         // 채널내 최대 유저수 설정
    //         // ex : /MODE #mychat +l 7 // 7명으로 제한
    //         // ex : /MODE #mychat -l   // 10명으로 제한
	// 		case 'l':
    //         {
    //             if (active && args[3].empty())
    //             {
    //                 client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "MODE"));
    //                 return;
    //             }
    //             channel->SetLimit(active ? atoi(args[present].c_str()) : 0);
    //             channel->Broadcast(RPL_MODE(client->GetPrefix(), channel->GetName(), (active ? "+l" : "-l"), (active ? args[present] : "")));
    //             break;
    //         }
    //         default:
    //         break;
    //     }
    //     // 다음인자가 있음
    //     i++;
    // }
}
