#include "SignIn.h"

#include <QApplication>

char ID[32];
char fingerPrint[32];


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    SignIn signIn;
    int result = signIn.exec();
    qDebug()<<result;
    application.exec();
    return 0;
}
