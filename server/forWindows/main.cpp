#include <iostream>
#include <stdlib.h>
/*************************/
//#include "md5.h"
#include "network.h"
#include "userTable.h"
#include "execOrder.h"

using namespace std;

int main(int argc, char * argv[]){
    if(argc!=2){
        cout<<"Please input an argument as the port"<<endl;
        cout<<"Program ending"<<endl;
        exit(1);
    }
    //init_ netWork
        int port;
        port=atoi(argv[1]);
        Port udpPort(port);
        cout<<"Network init_ed succesfully! Now using port: "<<port<<endl;
    //init_ userTable
        UserTable userTable;
        cout<<"userTable set!"<<endl;
    while(1){
        Message message=udpPort.getMessage();
        execOrders(message,udpPort,userTable);
    }
    
}

