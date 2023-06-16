#include "Socket.h"

Socket::~Socket()
{
	close();
}


int Socket::bind(std::string address, unsigned short port)
{
	hostAddr.sin_port = htons(port);
	
	inet_pton(familyType, address.c_str(), &hostAddr.sin_addr);
	
	if (cs::bind(host, (SOCKADDR*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR)
	{
		#ifdef DEBUG
		std::cout << "Binding failed with error " << WSAGetLastError() << std::endl;
		#endif // DEBUG
		return WSAGetLastError();
	}
	return 0;
}

int Socket::listen(unsigned int conum)
{
	if (cs::listen(host, conum) == SOCKET_ERROR)
	{
		#ifdef DEBUG
		std::cout << "Listen Failed with error" << WSAGetLastError() << std::endl;
		#endif // DEBUG
		return WSAGetLastError();
	}
	return 0;
}

int Socket::connect(std::string address, unsigned short port)
{
	connectionAddr.sin_family = familyType;
	connectionAddr.sin_port = htons(port);
	inet_pton(familyType, address.c_str(), &connectionAddr.sin_addr);

	connection = host;
#ifdef APP
retry_connection:
#endif // APP
	if (cs::connect(connection, (SOCKADDR*)&connectionAddr, sizeof(connectionAddr)) == SOCKET_ERROR)
	{
		#ifdef DEBUG
		std::cout << "Connection failed with error " << WSAGetLastError() << std::endl;
		#endif // DEBUG
		#ifdef APP
		if (WSAGetLastError() == 10061)
		{
			int response = MessageBox(NULL, (LPCWSTR)L"No connection could be made because the target machine actively refused it!", L"Error 0x" + WSAGetLastError(), MB_ICONERROR | MB_RETRYCANCEL);
			if (response == 4)
				goto retry_connection;
			else
				exit(1);
			return WSAGetLastError();
		}
		#endif // APP
		return WSAGetLastError();
	}
	return 0;
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

RecvFrom Socket::recvfrom(unsigned int length)
{
	std::vector<char> RecvBuffer(length);
	struct sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);
	if (cs::recvfrom(host, &RecvBuffer[0], length, 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize) == SOCKET_ERROR)
	{
		#ifdef DEBUG
		std::cout << "Error while trying to recive information the socket -> " << WSAGetLastError() << std::endl;
		#endif // DEBUG
		return RecvFrom{ NONE,0,0, std::string(WSAGetLastError(),0) };
	}
	char str[INET_ADDRSTRLEN];
	inet_ntop(familyType, &(SenderAddr.sin_addr), str, INET_ADDRSTRLEN);
	return RecvFrom{FamilyTypes(SenderAddr.sin_family),str, SenderAddr.sin_port, std::string(RecvBuffer.begin(), RecvBuffer.end())};
}

int Socket::sendto(Connection* con, std::string data)
{
	if (cs::sendto(host, data.c_str(), data.size(), 0, (SOCKADDR*)con->get_connection(), *con->size()) == SOCKET_ERROR)
		return WSAGetLastError();
	
	return 0;
}


Connection* Socket::accept()
{
	int connectionAddrLength = sizeof(connectionAddr);
	connection = cs::accept(host, (SOCKADDR*)&connectionAddr, &connectionAddrLength);
	if (connection == INVALID_SOCKET)
	{
		#ifdef DEBUG
		std::cout << "Accept Failed with error" << WSAGetLastError() << std::endl;
		#endif // DEBUG
		return 0;
	}
	
	Connection* cn = new Connection(connection, connectionAddr);
	return cn;
}

int Socket::setsockopt(int level, int optname, const char* optval)
{
	if (cs::setsockopt(host, level, optname, optval, sizeof(optval)) == INVALID_SOCKET)
	{
		#ifdef DEBUG
		std::cout << "SetSockOpt failed with error " <<  WSAGetLastError() <<std::endl;
		#endif // DEBUG
		return WSAGetLastError();
	}
	return 0;
}

int Socket::close()
{
	if (cs::closesocket(connection) == SOCKET_ERROR)
		return WSAGetLastError(); 
	return 0;
}
