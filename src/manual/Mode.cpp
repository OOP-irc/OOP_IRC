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
// ex:      MODE #Finnish +o Kilroy // #Finnish 채널에서 Kilroy에게 'chanop'권한을 부여합니다.
//          MODE 

void    Mode::Execute(Client* client, std::vector<std::string> args)
{
    // hanling errors

    if (args.size() < 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "MODE"));
        return;
    }
    
    std::string target = args.at(0);
    
    Channel *channel = mServer->GetChannel(target); //MODE on clients not implemented
    if (!channel)
    {
        client->SendErrorToClient(Log::GetERRNOSUCHCHANNEL(client->GetNickname(), target));
        return;
    }

    if (channel->GetClientOperator() != client)
    {
        client->SendToClient(Log::GetCHANOPRIVSNEEDED(client->GetNickname(), target));
        return;
    }

    // changing the mode

	int i = 0, p = 2;
	char c;
    
    while ((c = args[1][i]))
    {
        char prev_c = i > 0 ? args[1][i - 1] : '\0';
        bool active = prev_c == '+';

        switch (c) 
        {
			case 'l':
            {
                channel->set_limit(active ? atoi(args[p].c_str()) : 0);
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
			case 'k':
            {
                channel->set_key(active ? args[p] : "");
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
            default:
            break;
        }
        i++;
    }
}
