#include <iostream>
#include "Socket.h"

int main()
{	
	/*
	Socket sc(IPv4, TCP);

	sc.bind("127.0.0.1",10000);
	sc.listen();

	Connection* client = sc.accept();
	std::cout << client->recv(12) << std::endl;
	client->send("Hola mundo!");
	client->close();
	*/
	
	Connection cn(IPv4, TCP);
	cn.connect("127.0.0.1", 10000);
	cn.send("Hola mundo!");
	std::cout << cn.recv(12) << std::endl;
	cn.close();
	
	return 0;
}