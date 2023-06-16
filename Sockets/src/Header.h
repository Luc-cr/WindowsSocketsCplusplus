#pragma once
#include <iostream>
#include <vector>

namespace cs
{
	#include <WS2tcpip.h>
	#include <winsock2.h>
} using namespace cs;

#include "Exceptions.h"

#pragma comment(lib, "ws2_32.lib")

class SocketError;
class BasicSockets;
class Connection;
class Socket;


enum FamilyTypes
{
	NONE = 0,
	IPv4 = 2,
	IPv6 = 23,
	Bluetooth = 32,
};

enum ConnectionTypes
{
	TCP = 1,
	UDP = 2,
	RAW = 3,
};

struct RecvFrom
{
	FamilyTypes family;
	std::string ip;
	unsigned short port;
	std::string data;
};