#include "info.h"


Info::Info()
{}

Info::Info(QByteArray udpPack, QString ipSender, int portSender, int channel, float speed, float downloaded, bool downloading)
{
	this->channel = channel;
	this->downloaded = downloaded;
	this->downloading = downloading;
	this->ipSender = ipSender;
	this->portSender = portSender;
	this->speed = speed;
	this->udpPack = udpPack;
}

Info::~Info()
{}

void Info::setDownloading(bool downloading)
{
	this->downloading = downloading;
}

void Info::setIpSender(QString ipSender)
{
	this->ipSender = ipSender;
}

void Info::setPortSender(int portSender)
{
	this->portSender = portSender;
}

void Info::setChannel(int channel)
{
	this->channel = channel;
}

void Info::setSpeed(float speed)
{
	this->speed = speed;
}

void Info::setDownloaded(float downloaded)
{
	this->downloaded = downloaded;
}

void Info::setUdpPack(QByteArray udpPack)
{
	this->udpPack = udpPack;
}

bool Info::getDownloading() const
{
	return downloading;
}

QString Info::getIpSender() const
{
	return ipSender;
}

int Info::getPortSender() const
{
	return portSender;
}

int Info::getChannel() const
{
	return channel;
}

float Info::getSpeed() const
{
	return speed;
}

float Info::getDownloaded() const
{
	return downloaded;
}

QByteArray Info::getUdpPack() const
{
	return this->udpPack;
}

void Info::addToUdpPackage(QByteArray addingUdpPack)
{
	this->udpPack.append(addingUdpPack);
}
