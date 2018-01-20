#ifndef EXEC_ORDERS_H
#define EXEC_ORDERS_H

#include <string>
#include "network.h"
#include "userTable.h"

void execOrders(const Message & order, Port & udpPort, UserTable & userTable);

#endif