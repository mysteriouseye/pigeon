#ifndef USER_TABLE_H
#define USER_TABLE_H

#include <map>
#include <string>

struct UserInfo
{
    char ID[32];
    char fingerPrint[32]; //MD5_32
    unsigned char address[6];// lower 4 chars for IPV4, higher 2 chars for port
    bool isOnline; 
};


class UserTable
{
public:
    UserTable();
    bool addUser(const UserInfo user);
    UserInfo getUserbyId(const char * ID);
    bool setFingerPrint(const char * ID, const char* oldFingerPrint, const char * newFingerPrint);
    bool changeUserAddress(const char * ID, const char * fingerPrint, const unsigned char * address); //also used as bool userBackOnLine(...)
    bool userOffLine(const char * ID);
private:
    std::map<std::string, UserInfo> dataBase;
};

#endif