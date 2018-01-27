#include <iostream>
#include <WinSock2.h>


using namespace std;

int main(){
    WSADATA wsaData;
    int port=1104;

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        cout<<"WinSock loading error!"<<endl;
        return 1;
    }
    SOCKET sockSrv=socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(port);
    addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    if(bind(sockSrv,(LPSOCKADDR)&addrSrv,sizeof(SOCKADDR_IN))==SOCKET_ERROR){
        cout<<"bind Failed"<<endl;
        return 2;
    }
    if(listen(sockSrv,10)==SOCKET_ERROR){
        cout<<"listen Failed"<<endl;
        return 3;
    }

    SOCKADDR_IN addrClient;
    int len=sizeof(SOCKADDR);

    while(1){
        SOCKET sockConn = accept(sockSrv,(SOCKADDR *) & addrClient, &len);
        if(sockConn==SOCKET_ERROR){
            cout<<"accept Failed"<<endl;
            break;
        }
        char recvBuf[100];
        memset(recvBuf,0,sizeof(recvBuf));
        while(1){
            int ret;
            ret=recv(sockConn,recvBuf,sizeof(recvBuf),0);
            cout<<ret;
            if(ret==-1)
                break;
            cout<<recvBuf<<endl;
        }
        closesocket(sockConn);
    }
    closesocket(sockSrv);
    WSACleanup();
    cout<<"Hello!"<<endl;
    return 0;
}