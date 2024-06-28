#pragma once

#include <QString>

class Info
{
public:
	Info();
	Info(QString udpPack, QString ipSender, int portSender, int channel, float speed = 0, float downloaded = 0, bool downloading = false);
	~Info();

	void setDownloading(bool downloading);
	void setIpSender(QString ipSender);
	void setPortSender(int portSender);
	void setChannel(int channel);
	void setSpeed(float speed);
	void setDownloaded(float downloaded);
	void setUdpPack(QString udpPack);

	bool getDownloading() const;
	QString getIpSender() const;
	int getPortSender() const;
	int getChannel() const;
	float getSpeed() const;
	float getDownloaded() const;
	QString getUdpPack() const;

	void addToUdpPackage(QString addingUdpPack);

private:
	bool downloading;
	QString ipSender;
	int portSender;
	int channel;
	float speed;
	float downloaded;
	QString udpPack;
};
