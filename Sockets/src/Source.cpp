#include <iostream>
#include "Socket.h"
/*
class Server :public Socket
{
public:
	Server(FamilyTypes family, ConnectionTypes connection) : Socket(family, connection) {};
	~Server()
	{
		for (int i = 0; i < connections.size(); ++i)
		{
			connections[i]->close();
			delete connections[i];
		}
	}
	
	Connection* accept() override 
	{
		Connection* new_connection = Socket::accept();
		connections.push_back(new_connection);
		return new_connection;
	}
	std::vector<Connection*> connections;
};
*/
int main()
{
	
	/*Socket sc(IPv4, UDP);
	Connection con(IPv4, "127.0.0.1", 10000);
	sc.bind("127.0.0.1", 10001);
	sc.sendto(&con, "Hola Mundo!");
	std::cout << sc.recvfrom(&con, 12) << std::endl;
	MessageBox(NULL, (LPCWSTR)L"La conexion finalizo correctamente sin ningun error!", L":)", NULL);
	*/
	Socket sc(IPv4, UDP);
	Connection con(IPv4, "127.0.0.1", 10012);
	sc.bind("127.0.0.1", 10000);
	std::cout << sc.recvfrom(12).data << std::endl;
	sc.sendto(&con, "Hola Mundo!");
	
	/*
	Server sc(IPv4, TCP);

	sc.bind("127.0.0.1", 10000);
	sc.listen();

	sc.accept();
	std::cout << sc.connections[0]->recv(12) << std::endl;
	sc.connections[0]->send("Hola mundo!");
	sc.connections[0]->close();
	*/
	/*
	Socket sokc(IPv4, TCP);
	sokc.connect("127.0.0.1", 10000);
	sokc.send("Hola mundo!");
	std::cout << sokc.recv(12) << std::endl;
	sokc.close();
	MessageBox(NULL, (LPCWSTR)L"La conexion finalizo correctamente sin ningun error!", L":)", NULL);
	*/
	/*
	Connection cn(IPv4, TCP);
	cn.connect("127.0.0.1", 10000);
	cn.send("Hola mundo!");
	std::cout << cn.recv(12) << std::endl;
	cn.close();
	MessageBox(NULL, (LPCWSTR)L"La conexion finalizo correctamente sin ningun error!", L":)", NULL);
	*/
	return 0;
}
