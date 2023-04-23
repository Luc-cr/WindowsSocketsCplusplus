#include "BasicSockets.h"

BasicSockets::BasicSockets(FamilyTypes family, ConnectionTypes connection)
{
	if (WSAStartup(MAKEWORD(2, 2), &SocketDLL)) // Start WSA service 
	{
		std::cout << "Error while trying to start WSA.dll" << std::endl; 
		exit(1);
	}

	hostAddr.sin_family = family;

	this->familyType = family;
	this->connectionType = connection;

	int protocol;
	switch (connection)
	{
	case TCP:
		protocol = IPPROTO_TCP;
		break;
	case UDP:
		protocol = IPPROTO_UDP;
		break;
	case RAW:
		break;
	default:
		break;
	}

	host = cs::socket(family, connection, protocol);
	if (host == INVALID_SOCKET)
	{
		std::cout << "Socket Creation failed with error " << WSAGetLastError() << std::endl;
		exit(1);
	}
}

BasicSockets::BasicSockets(SOCKET Socket, sockaddr_in ConnectionInfo)
{
	connection = Socket;
	connectionAddr = ConnectionInfo;

	char ip[INET_ADDRSTRLEN];
	inet_ntop(connectionAddr.sin_family, &connectionAddr.sin_addr, ip, INET_ADDRSTRLEN);
}

