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
#include <QMessageBox>

#include "globalViables.h"
#include "userRegister.h"

bool strcmp(const char * str_1, const char * str_2, uint64_t maxsize);

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
    QMessageBox wait;

    UserRegister registerInterface;

    void signInReplyed();
    void success();
    void openRegisterInterface();
};


#endif // SIGNIN_H
