#include "Connection.h"

int Connection::send(std::string data)
{
	if (cs::send(connection, data.c_str(), (size_t)data.size(), 0) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	return 0;
}

std::string Connection::recv(unsigned int length)
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

int Connection::close()
{
	if (cs::closesocket(connection) == SOCKET_ERROR)
		return WSAGetLastError();
	
	return 0;
}
