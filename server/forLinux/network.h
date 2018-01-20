#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>

struct WSADATA_INIT;

struct Message
{
    SOCKADDR_IN socket;
    std::vector<char> content;
};

class Port
{
public:
    Port(int & port);
    Message getMessage();
    bool sendMessage(const std::string & content, const std::string & ip, const unsigned short port);
private:
    static WSADATA_INIT wsd_INIT;
    SOCKET udpSocket;
};

#endif