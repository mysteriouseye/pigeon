#ifndef GLOBALVIABLES_H
#define GLOBALVIABLES_H
#include <string>
#include <QUdpSocket>

extern char ID[32];
extern char fingerPrint[32];
extern std::string serverIP;
extern unsigned short serverPort;

extern QUdpSocket network;

#define FOUR_OFFSET 4
#define THREE_SIX_OFFSET 36
#define SIX_EIGHT_OFFSET 68
#define THREE_TWO_LENGTH 32

#endif // GLOBALVIABLES_H
