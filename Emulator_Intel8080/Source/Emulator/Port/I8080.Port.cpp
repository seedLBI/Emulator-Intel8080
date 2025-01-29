#include "I8080.Port.h"

I8080_Port::I8080_Port(uint8_t port)
{
	this->port = port;
}

void I8080_Port::SetInput(const uint8_t& value)
{

}

uint8_t  I8080_Port::GetOutput()
{
	return 0;
}

uint8_t I8080_Port::GetPort()
{
	return port;
}

void  I8080_Port::Reset()
{

}