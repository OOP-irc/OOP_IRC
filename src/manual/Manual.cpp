/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manual.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:35:22 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 19:38:11 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manual/Manual.hpp"

Manual::Manual(Server* server, bool auth) 
    : mServer(server), mAuth(auth) 
{
}

Manual::~Manual() 
{
}

bool    Manual::AuthRequired() const 
{ 
    return mAuth;
}
