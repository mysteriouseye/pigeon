#ifndef USERREGISTER_H
#define USERREGISTER_H

#include "md5.h"
#include "globalviables.h"


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

bool strcmp(const char * str_1, const char * str_2, uint64_t maxsize);

class UserRegister : public QDialog
{
    Q_OBJECT
public:
    UserRegister(QWidget * parent);
    ~UserRegister();
private:
    QLabel
        * userID,
        * userPassword,
        * confirmPassword;
    QLineEdit
        * inputID,
        * inputPassword,
        * inputConfirm;
    QHBoxLayout
        * IDLine,
        * passwordLine,
        * confirmLine;
    QVBoxLayout * layout;
    QPushButton * OK;
    QMessageBox
        * messageBox;
    void sendRequest();
    void getReply();
};

#endif // USERREGISTER_H
