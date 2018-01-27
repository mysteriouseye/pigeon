#include "network.h"
#include <stdlib.h>
#include <iostream>

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

WSADATA_INIT Port::wsd_INIT;

Port::Port(int & port)
{
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
}

Message Port::getMessage(){
    char buffer[4096];
    memset(buffer,0,sizeof(buffer));
    Message toReturn;
    int len=sizeof(SOCKADDR);
    recvfrom(udpSocket,buffer,sizeof(buffer),0,(SOCKADDR *  )&toReturn.socket,&len);
    for(int i=0;i<4096;i++)
        toReturn.content.push_back(buffer[i]);
    return toReturn;
}

bool Port::sendMessage(const std::string & content, const std::string & ip, const unsigned short port){
    char buffer[4096];
    memset(buffer,0,sizeof(buffer));
    for(int i=0;i<4096;i++)
        buffer[i]=content[i];
    SOCKADDR_IN targetAddr;
    targetAddr.sin_family=AF_INET;
    targetAddr.sin_addr.S_un.S_addr=inet_addr(ip.c_str());
    targetAddr.sin_port=htons(port);
    sendto(udpSocket,buffer,sizeof(buffer),0,(SOCKADDR *)& targetAddr,sizeof(SOCKADDR));
    return true;
}