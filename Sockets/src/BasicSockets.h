#pragma once
#include "Header.h"

class BasicSockets
{
protected:
	BasicSockets() {};
	BasicSockets(FamilyTypes family, ConnectionTypes connection);
	BasicSockets(SOCKET Socket, struct sockaddr_in ConnectionInfo);

	virtual int bind(std::string address, unsigned short port) = 0;
	virtual int listen(unsigned int conum = 1) = 0;
	virtual int connect(std::string address, unsigned short port) = 0;
	virtual RecvFrom recvfrom(unsigned int length = 65527) = 0;
	virtual int sendto(Connection* con, std::string data) = 0;
	virtual int send(std::string data) = 0;
	virtual std::string recv(unsigned int length = 65527) = 0;
	virtual Connection* accept() = 0;
	virtual int close() = 0;
	virtual int setsockopt(int level, int optname, const char *optval) = 0;
	

	SOCKET host;
	SOCKET connection;
	
	struct sockaddr_in hostAddr;
	struct sockaddr_in connectionAddr;

	FamilyTypes familyType;
	ConnectionTypes connectionType;
private:
	WSADATA SocketDLL;
};

