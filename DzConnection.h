#ifndef DZCONNECTION
#define DZCONNECTION

#include<string>
#include<Aria.h>

// DzConnection conn(&robot,"COM1",DzConnectionType::SERIAL);
// DzConnection conn(&robot,"192.168.1.201",DzConnectionType::TCP);

enum DzConnectionType{SERIAL, TCP};
class DzConnection{
private:
	enum DzConnectionType connType;
	std::string connParameters;
	ArSerialConnection * serConn;
	ArTcpConnection * tcpConn;
	ArRobot *robot;
	int connErrorType;
	int portNumber;
public:
	DzConnection(ArRobot *rb, std::string cp="COM1", DzConnectionType ct=DzConnectionType::SERIAL, int pN=8101);
	~DzConnection();
	DzConnection(const DzConnection & conn) {}
	DzConnection& operator=(const DzConnection & conn){}
	bool tcpConnection();
	bool serialConnection();
	void connFailure();
};

#endif