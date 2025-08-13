#ifndef MOMENTO_H
#define MOMENTO_H


class Momento{
public:
	Momento();
	Momento(const int& portNumber);
	virtual ~Momento();
	int GetPortNumber();
protected:
	int portNumber = -1;
};



#endif // !MOMENTO_H
