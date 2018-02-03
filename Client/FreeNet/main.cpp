#include "signIn.h"

#include "globalViables.h"

#include <QApplication>

char ID[32];
char fingerPrint[32];
std::string serverIP="127.0.0.1";
unsigned short serverPort=12345;
QUdpSocket network;

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    SignIn signIn;
    int result = signIn.exec();
    qDebug()<<result;
    if(result){

    }
    application.exec();
    return 0;
}
