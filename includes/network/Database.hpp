
#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <sys/socket.h>
#include <sys/poll.h>

#include <string>
#include <vector>

class Client;
class Channel;

#include "Channel.hpp"
#include "Client.hpp"

// #include "response.hpp"


// 역할 : 클라이언트와 채널목록을 가지고 조회,추가,삭제,업데이트 CRUD를 수행해준다.

class Database
{
    private:
        // 클라이언트의 목록
        std::map<int, Client*>  _channels;

        // 채널의 목록        
        std::map<int, std::set<Channel*>>  _channels; // 한 클라이언트 여러채널 최대 10개

/*
    https://stackoverflow.com/questions/722268/using-map-containing-set-as-a-value
    The set is only copied in initialization. You are allowed to do something like

    myMap[myString].insert(myDouble);
    since map::operator[] returns a reference.
*/

    public:
        /* Constructor and Destructor */
        Database()   
        ~Database()


        /* 추가, 조회, 삭제 */

        //insert()
        
        //select()
        
        //delete()

        //업데이트는 채널에서?

        /* Getters */
        //채널 

        //클라이언트


};

#endif
