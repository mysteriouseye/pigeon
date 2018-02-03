#include "dialogManager.h"
#include "globalviables.h"

DialogManager::DialogManager()
{

}

DialogManager::~DialogManager(){
    char * message = new char [4096];
    memset(message,0,4096);
    message[0]='4';
    for(uint i=0;i<sizeof(ID);i++)
        message[i+FOUR_OFFSET]=ID[i];
    for(uint i=0;i<sizeof(fingerPrint);i++)
        message[i+THREE_SIX_OFFSET]=fingerPrint[i];
    QHostAddress serverAddress(serverIP.c_str());
    network.writeDatagram(message,serverAddress,12345);
    delete [] message;
}
