#pragma once
#include "Socket.h"

class Connection : public BasicSockets
{
public:
	explicit Connection(FamilyTypes family, std::string address, unsigned short port);
	explicit Connection(SOCKET Socket, sockaddr_in ConnectionInfo) : BasicSockets(Socket, ConnectionInfo) {};


	int send(std::string data) override;
	std::string recv(unsigned int length = 65527) override;
	int close() override;

	sockaddr_in* get_connection() { return &connectionAddr; }
	unsigned short get_port() { return connectionAddr.sin_port; }
	char* get_address();
	int* size() { return &sizeCon; }
protected:
	int sizeCon = 0;

private:
	int connect(std::string address, unsigned short port) override { return 0; }
	int bind(std::string address, unsigned short port) override { return 0; }
	int listen(unsigned int conum = 1) override { return 0; }
	int setsockopt(int level, int optname, const char* optval) override { return 0;}
	Connection* accept() override { return nullptr; }
	RecvFrom recvfrom(unsigned int length = 65527) override { return RecvFrom{NONE,0,0,0}; }
	int sendto(Connection* con,std::string data) override {return 0;}
};

