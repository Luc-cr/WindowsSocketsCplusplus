#pragma once
#include "BasicSockets.h"
#include "Connection.h"



class Socket : public BasicSockets
{
public:
	explicit Socket(FamilyTypes family, ConnectionTypes connection) : BasicSockets::BasicSockets(family, connection) {};
	explicit Socket(SOCKET Socket, sockaddr_in ConnectionInfo) : BasicSockets(Socket, ConnectionInfo) {};
	~Socket();

	void bind(std::string address, unsigned short port) override;
	void listen(unsigned int conum = 1) override;
	void connect(std::string address, unsigned short port) override;
	int send(std::string data) override;
	std::string recv(unsigned int length = 65527) override;
	Connection* accept() override;
	int close() override;
};

