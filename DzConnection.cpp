#include"DzConnection.h"

DzConnection::DzConnection(ArRobot *rb, std::string cp,DzConnectionType ct, int pN){
	this->connParameters=cp;
	this->connType=ct;
	this->serConn=NULL;
	this->tcpConn=NULL;
	this->robot=rb;
	this->portNumber=pN;
	//this->connErrorType=0;

	if(DzConnectionType::SERIAL==ct){
		this->serialConnection();
	}
	else if(DzConnectionType::TCP==ct){
		this->tcpConnection();
	}
	else 
		this->connFailure();
		return;
	return;
}
DzConnection::~DzConnection(){
	delete this->serConn;
	delete this->tcpConn;
	this->connFailure();
	return;
}
bool DzConnection::tcpConnection(){
	this->tcpConn=new ArTcpConnection();
	if((this->connErrorType=tcpConn->open(this->connParameters.c_str(),this->portNumber))!=0){
		this->connFailure();
		return false;
	}
	this->robot->setDeviceConnection(this->tcpConn);

	if(!robot->blockingConnect())
	{
		this->connFailure();
		return false;
	}
	return true;
}
bool DzConnection::serialConnection(){
	this->serConn=new ArSerialConnection();
	if((this->connErrorType=serConn->open(this->connParameters.c_str()))!=0){
		this->connFailure();
		return false;
	}
	this->robot->setDeviceConnection(this->serConn);

	if(!robot->blockingConnect())
	{
		this->connFailure();
		return false;
	}
	return true;
}
void DzConnection::connFailure(){
	// handle the connection failure
	Aria::shutdown();
	return;
}
