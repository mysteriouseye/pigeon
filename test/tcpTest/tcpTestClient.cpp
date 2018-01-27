#include <iostream>
#include <WinSock2.h>


using namespace std;

int main(){
    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        cout<<"WinSock loading error!"<<endl;
        return 1;
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(1104);
    addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    cout<<inet_ntoa(addrSrv.sin_addr)<<"  "<<ntohs(htons(1104))<<endl;
    SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
    if(sockClient==SOCKET_ERROR){
        cout<<"socket Failed";
        return 1;
    }
    cout<<"socket built"<<endl;
    if(connect(sockClient,(struct sockaddr *)&addrSrv , sizeof(addrSrv))==INVALID_SOCKET){
        cout<<"connect Failed";
        return 1;
    }
    cout<<"connected"<<endl;
    char buff[100]="Hello ,I am a client!";
    cout<<buff<<endl;
    send(sockClient,buff,sizeof(buff),0);
    while(1){
        cin>>buff;
        send(sockClient,buff,sizeof(buff),0);
    }
    closesocket(sockClient);
    WSACleanup();
    return 0;
}