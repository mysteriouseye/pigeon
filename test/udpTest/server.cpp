#include "udp.h"

using namespace std;

int main()
{
    unsigned short port;
    cin>>port;
    udpPort udp(port);
    Message message;
    message=udp.getMessage();
    cout<<message.content;
    udp.sendMessage("O my God!","127.0.0.1",ntohs(message.socket.sin_port));
    return 0;
}
