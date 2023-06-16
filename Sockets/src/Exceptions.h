#pragma once
#include <iostream>

class WsaStartupError : public std::runtime_error
{
public:
	WsaStartupError() throw() : std::runtime_error("Error while trying to start WSA") {};
	virtual char const* what() const throw() { return std::exception::what(); }
};

class SocketCreationFailed : public std::runtime_error
{
public:
	SocketCreationFailed(unsigned short ErrCode) throw() : std::runtime_error("Socket Creation failed with error " + ErrCode) {};
	virtual char const* what() const throw() { return std::exception::what(); }
};
