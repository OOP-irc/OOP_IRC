/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:37:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/23 19:54:33 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/Server.hpp"

Server::Server(const std::string &port, const std::string &password)
    : _host("127.0.0.1"), _port(port), _password(password)
{

    _sock = create_socket();
    // _parser = new Parser(this);
}




