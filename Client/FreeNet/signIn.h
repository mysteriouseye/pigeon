#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDebug>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "globalViables.h"

class SignIn: public QDialog
{
public:
    SignIn();
    ~SignIn();
    void OK();
private:
    QLabel userID;
    QLabel password;
    QLineEdit inputID;
    QLineEdit inputPassword;
    QPushButton confirm;
    QPushButton userRegister;
    QVBoxLayout vLayout;
    QGridLayout gLayout;
    void signInReplyed();
    void success();
};


#endif // SIGNIN_H
