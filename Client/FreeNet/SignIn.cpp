#include "SignIn.h"

#include <QDebug>

SignIn::SignIn():
    userID("ID"),
    password("PWD"),
    inputID(""),
    inputPassword(""),
    confirm("Sign In"),
    login("I do not have an account")
{
    gLayout.addWidget(&userID,0,0);
    gLayout.addWidget(&password,1,0);
    gLayout.addWidget(&inputID,0,1);
    gLayout.addWidget(&inputPassword,1,1);
    vLayout.addLayout(&gLayout);
    vLayout.addWidget(&confirm);
    vLayout.addWidget(&login);
    setLayout(&vLayout);
    setWindowTitle("Sign In");
    connect(&confirm,&QPushButton::clicked,this,&SignIn::OK);
}

SignIn::~SignIn(){

}
