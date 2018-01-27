run : request.exe
	./request.exe

request.exe : main.o md5.o network.o
	g++ main.o md5.o network.o -lwsock32 -o request

main.o : main.cpp md5.h network.h
	g++ main.cpp -c

md5.o : md5.cpp md5.h
	g++ md5.cpp -c

network.o : network.cpp network.h
	g++ network.cpp -c