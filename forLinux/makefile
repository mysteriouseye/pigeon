server : main.o execOrder.o network.o userTable.o
	g++ main.o execOrder.o network.o userTable.o -o server

main.o : main.cpp network.h userTable.h execOrder.h
	g++ main.cpp -c

execOrder.o : execOrder.cpp execOrder.h network.h userTable.h
	g++ execOrder.cpp -c

network.o : network.cpp network.h 
	g++ network.cpp -c

userTable.o : userTable.cpp userTable.h
	g++ userTable.cpp -c
