#include "Connection.h"

Connection::Connection(FamilyTypes family, std::string address, unsigned short port)
{
	connectionAddr.sin_family = family;
	connectionAddr.sin_port = htons(port);
	inet_pton(family, address.c_str(), &connectionAddr.sin_addr);
	sizeCon = sizeof(connectionAddr);
}

int Connection::send(std::string data)
{
	if (cs::send(connection, data.c_str(), (size_t)data.size(), 0) == SOCKET_ERROR)
		return WSAGetLastError();
	
	return 0;
}

std::string Connection::recv(unsigned int length)
{
	std::vector<char> RecvBuffer(length);
	if (cs::recv(connection, &RecvBuffer[0], length, 0) == SOCKET_ERROR)
	{
		#ifdef DEBUG
		std::cout << "Error while trying to recive information the socket -> " << WSAGetLastError() << std::endl;
		#endif // DEBUG

		#ifdef APP
		if (WSAGetLastError() == 10054)
		{
			int msg = MessageBox(NULL, L"The connection was reset by the peer", L"Error 0x" + WSAGetLastError(), MB_ICONEXCLAMATION | MB_OK);
			exit(1);
		}
		#endif // APP
		return std::string(WSAGetLastError(), 0);
	}
	return std::string(RecvBuffer.begin(), RecvBuffer.end());
}

int Connection::close()
{
	if (cs::closesocket(connection) == SOCKET_ERROR)
		return WSAGetLastError();
	
	return 0;
}

char* Connection::get_address()
{
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(connectionAddr.sin_addr), ip, INET_ADDRSTRLEN);
	return ip;
}
