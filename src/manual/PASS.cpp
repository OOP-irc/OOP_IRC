/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:53:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/27 19:55:51 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Manual.hpp"

Ping::Ping(Server* server) : Manual(server) {}

Ping::~Ping() {}

void    Ping::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {



    }
}

