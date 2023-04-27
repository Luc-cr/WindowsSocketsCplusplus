#pragma once
#include "Socket.h"

class Connection : public BasicSockets
{
public:
	explicit Connection(SOCKET Socket, sockaddr_in ConnectionInfo) : BasicSockets(Socket, ConnectionInfo) {};

	int send(std::string data) override;
	std::string recv(unsigned int length = 65527) override;
	int close() override;

private:
	void connect(std::string address, unsigned short port) override {};
	void bind(std::string address, unsigned short port) override {};
	void listen(unsigned int conum = 1) override {};
	Connection* accept() override { return nullptr; }
	
};

