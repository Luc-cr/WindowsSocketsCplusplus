#pragma once
#include "BasicSockets.h"
#include "Connection.h"

class Socket : public BasicSockets
{
public:
	explicit Socket(FamilyTypes family, ConnectionTypes connection) : BasicSockets::BasicSockets(family, connection) {};
	explicit Socket(SOCKET Socket, sockaddr_in ConnectionInfo) : BasicSockets(Socket, ConnectionInfo) {};
	~Socket();
	
	// TCP
	int bind(std::string address, unsigned short port) override;
	int listen(unsigned int conum = 1) override;
	int setsockopt(int level, int optname, const char* optval) override;
	
	Connection* accept() override;
	int connect(std::string address, unsigned short port) override;
	int send(std::string data) override;
	std::string recv(unsigned int length = 65527) override;
	
	// UDP
	RecvFrom recvfrom(unsigned int length = 65527) override;
	int sendto(Connection* con, std::string data) override;

	int close() override;
};

