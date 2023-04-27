#include "Socket.h"

Socket::~Socket()
{
	close();
}


void Socket::bind(std::string address, unsigned short port)
{
	hostAddr.sin_port = htons(port);
	
	inet_pton(familyType, address.c_str(), &hostAddr.sin_addr);
	
	if (cs::bind(host, (SOCKADDR*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR)
	{
		std::cout << "Binding failed with error " << WSAGetLastError() << std::endl;
		return;
	}
}

void Socket::listen(unsigned int conum)
{
	if (cs::listen(host, conum) == SOCKET_ERROR)
	{
		std::cout << "Listen Failed with error" << WSAGetLastError() << std::endl;
	}
	return;
}

void Socket::connect(std::string address, unsigned short port)
{
	connectionAddr.sin_family = familyType;
	connectionAddr.sin_port = htons(port);
	inet_pton(familyType, address.c_str(), &connectionAddr.sin_addr);

	connection = host;

retry_connection:
	if (cs::connect(connection, (SOCKADDR*)&connectionAddr, sizeof(connectionAddr)) == SOCKET_ERROR)
	{
		std::cout << "Connection failed with error " << WSAGetLastError() << std::endl;
		if (WSAGetLastError() == 10061)
		{
			int response = MessageBox(NULL, (LPCWSTR)L"No connection could be made because the target machine actively refused it!", L"Error 0x" + WSAGetLastError(), MB_ICONERROR | MB_RETRYCANCEL);
			if (response == 4)
				goto retry_connection;
			else
				exit(1);
		}
	}
}

int Socket::send(std::string data)
{
	if (cs::send(connection, data.c_str(), (size_t)data.size(), 0) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	return 0;
}

std::string Socket::recv(unsigned int length)
{
	std::vector<char> RecvBuffer(length);
	if (cs::recv(connection, &RecvBuffer[0], length, 0) == SOCKET_ERROR)
	{
		std::cout << "Error while trying to recive information the socket -> " << WSAGetLastError() << std::endl;
		if (WSAGetLastError() == 10054)
		{
			int msg = MessageBox(NULL, L"The connection was reset by the peer", L"Error 0x" + WSAGetLastError(), MB_ICONEXCLAMATION | MB_OK);
			exit(1);
		}
	}
	return std::string(RecvBuffer.begin(), RecvBuffer.end());
}


Connection* Socket::accept()
{
	int connectionAddrLength = sizeof(connectionAddr);
	connection = cs::accept(host, (SOCKADDR*)&connectionAddr, &connectionAddrLength);
	if (connection == INVALID_SOCKET)
		std::cout << "Accept Failed with error" << WSAGetLastError() << std::endl;
	
	Connection* cn = new Connection(connection, connectionAddr);
	return cn;
}

int Socket::close()
{

	if (cs::closesocket(connection) == SOCKET_ERROR)
		return WSAGetLastError(); 
	return 0;
}
