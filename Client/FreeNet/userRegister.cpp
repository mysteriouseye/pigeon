#include "userRegister.h"

UserRegister::UserRegister(QWidget * parent) :
    QDialog(parent),
    userID(new QLabel("ID       ")),
    userPassword(new QLabel("PWD      ")),
    confirmPassword(new QLabel("Repet PWD")),
    inputID(new QLineEdit()),
    inputPassword(new QLineEdit()),
    inputConfirm(new QLineEdit()),
    IDLine(new QHBoxLayout()),
    passwordLine(new QHBoxLayout()),
    confirmLine(new QHBoxLayout()),
    layout(new QVBoxLayout()),
    OK(new QPushButton("Register Now!")),
    messageBox(new QMessageBox())
{
    IDLine->addWidget(userID);
    IDLine->addWidget(inputID);

    passwordLine->addWidget(userPassword);
    passwordLine->addWidget(inputPassword);

    confirmLine->addWidget(confirmPassword);
    confirmLine->addWidget(inputConfirm);

    layout->addLayout(IDLine);
    layout->addLayout(passwordLine);
    layout->addLayout(confirmLine);
    layout->addWidget(OK);

    setLayout(layout);
    setWindowTitle("Please register");
    connect(OK,&QPushButton::clicked,this,&UserRegister::sendRequest);
}

UserRegister::~UserRegister(){
    delete layout;  //It shall delete all those objects
}

void UserRegister::sendRequest(){
    qDebug()<<"Registering!";
    if(inputID->text().length()>0&&
       inputID->text().length()<=32&&
       inputPassword->text().length()>0&&
       inputConfirm->text()==inputPassword->text()){
        messageBox->setText("Registering, just a minute");
        qDebug()<<"B1";
        network.abort();//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        if(network.bind()!=true)
            exit(1);
        QHostAddress serverAddress(serverIP.c_str());
        char * message = new char[4096];
        memset(message,0,4096);
        message[0]='1';
        for(int i=0;i<inputID->text().length();i++)
            message[i+FOUR_OFFSET]=inputID->text().toStdString()[i];
        std::string fingerPrint = inputPassword->text().toStdString();
        MD5 md5(fingerPrint);
        fingerPrint=md5.md5();
        for(uint i=0;i<fingerPrint.length();i++)
            message[i+THREE_SIX_OFFSET]=fingerPrint[i];
        qDebug()<<message+4;
        connect(&network,&QUdpSocket::readyRead,this,&UserRegister::getReply);
        network.writeDatagram(message,4096,serverAddress,12345);
        delete [] message;
        messageBox->show();
    }
    else{
        QMessageBox canNotBeEmpty;
        canNotBeEmpty.setText("ID and Password cannot be empty, ID shall no longer than 32, the password should be the same");
        canNotBeEmpty.exec();
    }
}

void UserRegister::getReply(){
    char * message = new char[4096];
    memset(message,0,4096);
    qint64 messageLength;
    messageLength=network.readDatagram(message,4096);
    qDebug()<<"Got something!"<<messageLength;
    qDebug()<<message+FOUR_OFFSET;
    if(messageLength==4096&&message[0]=='1'){
        char successString[] = "Succeed!";
        messageBox->done(0);
        if(strcmp(successString,message+FOUR_OFFSET,sizeof(successString))){
            messageBox->setText("Succeed! Now you have an account!");
            messageBox->exec();
        }
        else{
            messageBox->setText(message+FOUR_OFFSET);
            messageBox->exec();
        }
    }
    else
        qDebug()<<"Something went wrong!";
    delete [] message;
}

