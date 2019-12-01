server : async_server.cpp Server.cpp
	g++ -c Server.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread
	g++ async_server.cpp Server.o -L /usr/lib/ -lboost_system -lboost_thread -lpthread -o server

client : async_client.cpp
	g++ -c SerClientver.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread
	g++ async_client.cpp -L /usr/lib/ -lboost_system -lboost_thread -lpthread -o client

clean :
	rm -f client server
