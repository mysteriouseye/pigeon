#include <iostream>
#include <stdio.h> //for atio();

#include "network.h"
#include "md5.h"

using namespace std;

int main(int argc, char * argv[]){
    unsigned short targetPort;
    if(argc!=2){
        cout<<"Input the port: ";
        cin>>targetPort;
    }
    else
        targetPort=atoi(argv[1]);
    int p =2000;
    Port port(p);
    cout<<"Port bind: "<<p<<endl;
    string message;
    for(int i=0;i<4096;i++)
        message.push_back('\0');
    message[0]='1';
    string ID = "test";
    for(int i=0;i<ID.length();i++)
        message[i+4]=ID[i];
    MD5 md5("Ab123456");
    string result=md5.md5();
    for(int i=0;i<result.length();i++)
        message[i+36]=result[i];
    cout<<message<<endl;
    port.sendMessage(message,"127.0.0.1",targetPort);
    cout<<"Message sent!"<<endl;
    Message returnMessage = port.getMessage();
    for(int i=0;i<returnMessage.content.size();i++)
        message[i]=returnMessage.content[i];
    cout<<message;
    return 0;
}
