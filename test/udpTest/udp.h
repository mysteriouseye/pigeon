#include <Winsock2.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using std::string;

struct WSADATA_INIT
{
    WSADATA wsd;
    WSADATA_INIT(){
        if(WSAStartup(MAKEWORD(2,2),&wsd) != 0){  
            std::cout<<"WSAStartup failed !"<<std::endl;
            exit(1);
        }
        std::cout<<"WSAStartup Finished !"<<std::endl;
    }
};

struct Message
{
    SOCKADDR_IN socket;
    string content;
};

class udpPort{
public:
    udpPort(unsigned short & port);
    Message getMessage();
    bool sendMessage(const string & content, const string & ip, const unsigned short port);
private:
    static WSADATA_INIT wsd_INIT;
    SOCKET udpSocket;

};

WSADATA_INIT udpPort::wsd_INIT;

udpPort::udpPort(unsigned short & port){
    udpSocket=socket(AF_INET,SOCK_DGRAM,0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port = htons(port);
    while(bind(udpSocket,(SOCKADDR *)& addrSrv,sizeof(SOCKADDR))==SOCKET_ERROR){
        addrSrv.sin_port=htons(++port);
        if(port>=65535){
            std::cout<<"No free ports"<<std::endl;
            exit(1);
        }
    }
    std::cout<<"Successfully bind port: "<<port<<std::endl;
}

Message udpPort::getMessage(){
    char buffer[4096];
    memset(buffer,0,sizeof(buffer));
    Message toReturn;
    int len=sizeof(SOCKADDR);
    recvfrom(udpSocket,buffer,sizeof(buffer),0,(SOCKADDR *  )&toReturn.socket,&len);
    for(int i=0;i<len;i++)
        toReturn.content.push_back(buffer[i]);
    return toReturn;    
}

bool udpPort::sendMessage(const string & content, const string & ip, const unsigned short port){
    char buffer[4096];
    memset(buffer,0,sizeof(buffer));
    strcpy(buffer,content.c_str());
    SOCKADDR_IN targetAddr;
    targetAddr.sin_family=AF_INET;
    targetAddr.sin_addr.S_un.S_addr=inet_addr(ip.c_str());
    targetAddr.sin_port=htons(port);
    sendto(udpSocket,buffer,content.length(),0,(SOCKADDR *)& targetAddr,sizeof(SOCKADDR));
    std::cout<<"Message sent!"<<std::endl;
    return true;
}