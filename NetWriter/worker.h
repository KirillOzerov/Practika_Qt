#pragma once

#include <QObject>
#include "qudpsocket.h"
#include "info.h"
#include "speedtracker.h"
#include <vector>
#include <QtNetwork>
#include <QFile>


class Worker : public QObject
{
	Q_OBJECT

public:
	Worker();
	~Worker();
	void setPath(QString fileWay);
private:
	QUdpSocket* udpSocket;
	QVector<SpeedTracker> times;
	QString ip;
	int channelNumber;
	quint16 senderPort;
	QString path;
public slots:
	void readingData();
	void getPort(int port);
	void stopSlot();
signals:
	void infoSend(Info info);
};
