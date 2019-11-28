server : async_server.cpp
	g++ async_server.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread -o server

client : async_client.cpp
	g++ async_client.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread -o client

clean :
	rm -f client server
