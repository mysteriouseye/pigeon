#include "userTable.h"

bool charArryCmp(const char * a,const char * b,const unsigned int size){
    for(unsigned int i=0;i<size;i++)
        if(a[i]!=b[i])
            return false;
    return true;
}

void charArryCpy(char * destination, const char * source ,const unsigned int size){
    for(unsigned int i=0;i<size;i++)
        destination[i]=source[i];
    return;
}



UserTable::UserTable():dataBase(){
    //void ditermination
}

bool UserTable::addUser(const UserInfo user){
    if(dataBase.find(user.ID)!=dataBase.end())
        return false;
    dataBase[user.ID]=user;
    return true;
}

UserInfo UserTable::getUserbyId(const char * ID){
    std::map<std::string, UserInfo>::iterator it=
        dataBase.find(ID);
    if(it==dataBase.end()){
        UserInfo nullUser;
        nullUser.ID[0]=0;
        return nullUser;
    }
    return dataBase[ID];
}

bool UserTable::setFingerPrint(const char * ID, const char* oldFingerPrint, const char * newFingerPrint){
    if(dataBase.find(ID)!=dataBase.end())
        if(charArryCmp(dataBase[ID].fingerPrint,oldFingerPrint,32)){
            charArryCpy(dataBase[ID].fingerPrint,newFingerPrint,32);
            return true;
        }
    return false;
}

bool UserTable::changeUserAddress(const char * ID, const char * fingerPrint, const unsigned char * address){ //also used as bool userBackOnLine(...)
    if(dataBase.find(ID)!=dataBase.end())
        if(charArryCmp(dataBase[ID].fingerPrint,fingerPrint,32)){
            for(int i=0;i<32;i++){
                dataBase[ID].address[i]=address[i];
            }
            dataBase[ID].isOnline=true;
            return true;
        }
    return false;
}

bool UserTable::userOffLine(const char* ID){
    if(dataBase.find(ID)!=dataBase.end()){
        dataBase[ID].isOnline=false;
        return true;
    }
    return false;
}
