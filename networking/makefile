server : async_server.cpp Server.cpp
	g++ -c Server.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread
	g++ async_server.cpp Server.o -L /usr/lib/ -lboost_system -lboost_thread -lpthread -o server

client : async_client.cpp Client.cpp
	g++ -c Client.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread -lboost_fiber
	g++ async_client.cpp Client.o -L /usr/lib/ -lboost_system -lboost_thread -lpthread -lboost_fiber -o client

server2 : async_server.cpp
	g++ async_server.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread -o server2

clean :
	rm -f client server *.o
