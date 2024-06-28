#pragma once

#include <QObject>
#include "qudpsocket.h"
#include "info.h"
#include "speedtracker.h"
#include <vector>
#include <QtNetwork>


class Worker : public QObject
{
	Q_OBJECT

public:
	Worker();
	~Worker();
private:
	QUdpSocket* udpSocket;
	QVector<SpeedTracker> times;
	QString ip;
	int channelNumber;
	quint16 senderPort;
public slots:
	void readingData();
	void getPort(int port);
	void stopSlot();
signals:
	void infoSend(Info info);
};
