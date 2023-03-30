#include "manual/Manual.hpp"

Mode::Mode(Server* server)
    : Manual(server) 
{
}

Mode::~Mode() 
{
}

<<<<<<< HEAD
// syntax:  MODE <nickname> <flags> (user)
//          MODE <channel> <flags> [<args>]
// o - give/take channel operator privilege;
// k - set/remove the channel key (password);
// l - set/remove the user limit to channel;
// b - set/remove ban mask to keep users out;
// e - set/remove an exception mask to override a ban mask;
// ex:      MODE #Finnish +o Kilroy // #Finnish 채널에서 Kilroy에게 'chanop'권한을 부여합니다.
//  
=======
// syntax: KICK <channel> <client> :[<message>]
>>>>>>> 1527e4018a6168db6bf862cc02bfd5b1897c9cc6

void    Mode::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "KICK"));
        return;
    }
    
    std::string target = args.at(0);
    
<<<<<<< HEAD
    //MODE on clients not implemented
    Channel *channel = mServer->GetChannel(target); 
    if (!channel)
=======
    Channel *chan = mServer->GetChannel(target);
    if (!chan)
>>>>>>> 1527e4018a6168db6bf862cc02bfd5b1897c9cc6
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

<<<<<<< HEAD
	int i = 0; 
    int p = 2;
	char chr;

// o - give/take channel operator privilege;
// k - set/remove the channel key (password);
// l - set/remove the user limit to channel;

    // args[0] == "#mychat"
    // args[1] == "+n"

    while ((chr = args[1][i]))
    {
        char prev_c = ((i > 0) ? args[1][i - 1] : '\0');
        bool active = (prev_c == '+');

        switch (chr)
        {
            // 오퍼레이터 권한 부여
            // ex : /MODE #mychat +o mikim2 //mikim2를 오퍼레이터로 변경
            //      /MODE #mychat -o mikim2
			case 'o':
            {
                // 닉네임으로 해당 닉네임 클라이언트가 채널에 속해 있는지 확인하기
                channel->AddClientOperator(active ? (args[p]) : "");
                channel->Broadcast(RPL_MODE(client->GetPrefix(), channel->GetName(), (active ? "+o" : "-o"), (active ? args[p] : "")));
                
                // 이게 뭘까
                // p += active ? 1 : 0;
                break;
            }
            // 채널의 비밀번호설정
            // ex : /MODE #mychat +k 1234
            //      /MODE #mychat -k
			case 'k':
            {
                channel->SetPassword(active ? args[p] : "");
                channel->Broadcast(RPL_MODE(client->GetPrefix(), channel->GetName(), (active ? "+k" : "-k"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
            // 채널내 최대 유저수 설정
            // ex : /MODE #mychat +l 7 // 7명으로 제한
            // ex : /MODE #mychat -l   // 10명으로 제한
			case 'l':
            {
                channel->SetLimit(active ? atoi(args[p].c_str()) : 0);
                channel->Broadcast(RPL_MODE(client->GetPrefix(), channel->GetName(), (active ? "+l" : "-l"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
            default:
            break;
        }
        i++;
    }
=======
	// int i = 0, p = 2;
	// char c;
    
    // while ((c = args[1][i]))
    // {
    //     char prev_c = i > 0 ? args[1][i - 1] : '\0';
    //     bool active = prev_c == '+';

    //     switch (c) 
    //     {
    //         case 'n':
    //         {
    //             channel->set_ext_msg(active);
    //             channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+n" : "-n"), ""));
    //             break;
    //         }
	// 		case 'l':
    //         {
    //             channel->set_limit(active ? atoi(args[p].c_str()) : 0);
    //             channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")));
    //             p += active ? 1 : 0;
    //             break;
    //         }
	// 		case 'k':
    //         {
    //             channel->set_key(active ? args[p] : "");
    //             channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")));
    //             p += active ? 1 : 0;
    //             break;
    //         }
    //         default:
    //         break;
    //     }
    //     i++;
>>>>>>> 1527e4018a6168db6bf862cc02bfd5b1897c9cc6
}
