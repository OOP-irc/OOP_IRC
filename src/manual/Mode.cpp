#include "manual/Manual.hpp"

Mode::Mode(Server* server) 
    : Manual(server) 
{
}

Mode::~Mode() 
{
}

// syntax: KICK <channel> <client> :[<message>]

void    Mode::Execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->SendErrorToClient(Log::GetERRNEEDMOREPARAMS(client->GetNickname(), "KICK"));
        return;
    }
    
    std::string target = args.at(0);
    
    Channel *chan = mServer->GetChannel(target);
    if (!chan)
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
}
