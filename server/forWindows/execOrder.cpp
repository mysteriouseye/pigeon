#include "execOrder.h"
#include <stdio.h>


void execOrders(const Message & order, Port & udpPort, UserTable & userTable){
    const std::vector<char> & message = order.content;
    const std::string IP = inet_ntoa(order.socket.sin_addr);
    const unsigned short port = ntohs(order.socket.sin_port);
    UserInfo newUser;
    std::string abcd[4];
    for(int i=0,j=0;i<IP.size();i++){
        if(IP[i]=='.')
            j++;
        else
            abcd[j].push_back(IP[i]);
    }
    std::string retMessage;
    //init retMessage
    for(int i=0;i<4096;i++) 
        retMessage.push_back('\0');
    //set newUser.ID
    bool endFlag=false;
    for(int i=0;i<32;i++){
        if(message[i+4]=='\0')
            endFlag=true;
        newUser.ID[i]=message[i+4];
        if(endFlag==true)
            newUser.ID[i]='\0';
    }
    char newFingerPrint[32];
    switch(message[0]){     //message[0] represents what service the client wants
        case '1':
            //get fingerPrint
            for(int i=0;i<32;i++)
                newUser.fingerPrint[i]=message[i+4+32];
            //set Address
            for(int i=0;i<4;i++)
                newUser.address[i]=atoi(abcd[i].c_str());
            newUser.address[4]=port%(unsigned short)256;
            newUser.address[5]=port/(unsigned short)256;
            newUser.isOnline==true;
            retMessage[0]='1';
            if(userTable.addUser(newUser)==true)
                strcpy(&retMessage[4],"Success!");
            else
                strcpy(&retMessage[4],"User already exist!");
            udpPort.sendMessage(retMessage,IP,port);
            break;
        case '2':
            for(int i=0;i<32;i++)
                newUser.fingerPrint[i]=message[i+4+32];
            for(int i=0;i<4;i++)
                newUser.address[i]=atoi(abcd[i].c_str());
            newUser.address[4]=port%(unsigned short)256;
            newUser.address[5]=port/(unsigned short)256;
            retMessage[0]='2';
            if(userTable.changeUserAddress(newUser.ID,newUser.fingerPrint,newUser.address)==true)
                strcpy(&retMessage[4],"Success!");
            else
                strcpy(&retMessage[4],"PassWord Error or No such Account!");
            udpPort.sendMessage(retMessage,IP,port);
            break;
        case '3':
            for(int i=0;i<32;i++)
                newUser.fingerPrint[i]=message[i+4+32];
            for(int i=0;i<32;i++)
                newFingerPrint[i]=message[i+4+32+32];
            retMessage[0]='3';
            if(userTable.setFingerPrint(newUser.ID,newUser.fingerPrint,newFingerPrint)==true)
                strcpy(&retMessage[4],"Success!");
            else
                strcpy(&retMessage[4],"PassWord Error or No such Account!");
            udpPort.sendMessage(retMessage,IP,port);
            break;
        case '4':
            retMessage[0]='4';
            if(userTable.userOffLine(newUser.ID)==true)
                strcpy(&retMessage[4],"Success!");
            else
                strcpy(&retMessage[4],"PassWord Error or No such Account!");
            udpPort.sendMessage(retMessage,IP,port);
            break;
        case '5':
            retMessage[0]='5';
            newUser=userTable.getUserbyId(newUser.ID);
            if(newUser.ID[0]=='\0')
                retMessage[4]='3';
            else if(newUser.isOnline==false)
                retMessage[4]='2';
            else{
                retMessage[4]='1';
                std::string userIP="";

                //there is no itoa() in linux , use sprintf()
                char * itoaBuffer = new char [10];
                for(int i=0;i<4;i++){
                    memset(itoaBuffer,0,sizeof(char[10]));
                    sprintf(itoaBuffer,"%d",newUser.address[i]);
                    userIP.append(itoaBuffer);
                    userIP.append(".");
                }
                userIP[userIP.length()-1]=':';
                memset(itoaBuffer,0,sizeof(char[10]));
                sprintf(itoaBuffer,"%d",int(newUser.address[5])*256+int(newUser.address[4]));
                userIP.append(itoaBuffer);
                for(int i=0;i<userIP.length();i++)
                    retMessage[i+8];
            }
            udpPort.sendMessage(retMessage,IP,port);
            break;
        default:
            udpPort.sendMessage(retMessage,IP,port);
    }
    return;
    //execOrder done!
}