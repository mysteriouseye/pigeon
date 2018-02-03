#include "signIn.h"
#include "globalViables.h"
#include "md5.h"

#include <QDebug>
#include <QMessageBox>

SignIn::SignIn():
    userID("ID"),
    password("PWD"),
    inputID(""),
    inputPassword(""),
    confirm("Sign In"),
    userRegister("I do not have any account")
{
    gLayout.addWidget(&userID,0,0);
    gLayout.addWidget(&password,1,0);
    gLayout.addWidget(&inputID,0,1);
    gLayout.addWidget(&inputPassword,1,1);
    vLayout.addLayout(&gLayout);
    vLayout.addWidget(&confirm);
    vLayout.addWidget(&userRegister);
    setLayout(&vLayout);
    setWindowTitle("Sign In");
    connect(&confirm,&QPushButton::clicked,this,&SignIn::OK);
}

void SignIn::OK(){
    if(inputID.text().length()>0&&
       inputID.text().length()<=32&&
       inputPassword.text().length()>0){
        QMessageBox wait(this);
        wait.setText("Signing in, just a minute");
        network.abort();//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(network.bind()!=true)
            exit(1);
        QHostAddress serverAddress(serverIP.c_str());
        char * message = new char[4096];
        memset(message,0,4096);
        message[0]='2';
        for(int i=0;i<inputID.text().length();i++)
            message[i+FOUR_OFFSET]=inputID.text().toStdString()[i];
        std::string fingerPrint = inputPassword.text().toStdString();
        MD5 md5(fingerPrint);
        fingerPrint=md5.md5();
        for(uint i=0;i<fingerPrint.length();i++)
            message[i+THREE_SIX_OFFSET]=fingerPrint[i];
        qDebug()<<message+4;
        connect(&network,&QUdpSocket::readyRead,this,&SignIn::signInReplyed);
        network.writeDatagram(message,serverAddress,12345);
        wait.exec();
        delete [] message;
    }
    else{
        QMessageBox canNotBeEmpty;
        canNotBeEmpty.setText("ID and Password cannot be empty, ID shall no longer than 32");
        canNotBeEmpty.exec();
    }
}

void SignIn::signInReplyed(){
    char * message = new char[4096];
    memset(message,0,4096);
    qint64 messageLength;
    messageLength=network.readDatagram(message,4096);
    qDebug()<<"Got something!"<<messageLength;
    if(messageLength==4096&&message[0]=='2'){
        char successString[] = "Success!";
        if(strcmp(successString,message+4))
            success();
    }
    delete [] message;
}

void SignIn::success(){
    for(int i=0;i<THREE_TWO_LENGTH;i++){
        ID[i]=inputID.text().toStdString()[i];
        fingerPrint[i]=MD5(inputPassword.text().toStdString()).md5()[i];
    }
    qDebug()<<"Sign in successfully!";
    done(1);
}

SignIn::~SignIn(){

}
