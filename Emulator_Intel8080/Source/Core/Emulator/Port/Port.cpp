#include "Port.h"

Port::Port(uint8_t port)
{
	this->port = port;
}

void Port::SetInput(const uint8_t& value)
{

}

uint8_t  Port::GetOutput()
{
	return 0;
}

uint8_t Port::GetPort()
{
	return port;
}

void  Port::Reset()
{

}