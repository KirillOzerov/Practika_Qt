#pragma once

#include <QString>

class Info
{
public:
	Info();
	Info(QByteArray udpPack, QString ipSender, int portSender, int channel, float speed = 0, float downloaded = 0, bool downloading = false);
	~Info();

	void setDownloading(bool downloading);
	void setIpSender(QString ipSender);
	void setPortSender(int portSender);
	void setChannel(int channel);
	void setSpeed(float speed);
	void setDownloaded(float downloaded);
	void setUdpPack(QByteArray udpPack);

	bool getDownloading() const;
	QString getIpSender() const;
	int getPortSender() const;
	int getChannel() const;
	float getSpeed() const;
	float getDownloaded() const;
	QByteArray getUdpPack() const;

	void addToUdpPackage(QByteArray addingUdpPack);

private:
	bool downloading;
	QString ipSender;
	int portSender;
	int channel;
	float speed;
	float downloaded;
	QByteArray udpPack;
};
