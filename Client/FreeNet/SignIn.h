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

class SignIn: public QDialog
{
public:
    SignIn();
    ~SignIn();
    void OK(){done(1);}
private:
    QLabel userID;
    QLabel password;
    QLineEdit inputID;
    QLineEdit inputPassword;
    QPushButton confirm;
    QPushButton login;
    QVBoxLayout vLayout;
    QGridLayout gLayout;
};


#endif // SIGNIN_H
