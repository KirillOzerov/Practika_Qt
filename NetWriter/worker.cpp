#include "info.h"
#include "worker.h"

Worker::Worker()
{
	udpSocket = new QUdpSocket(this);
	udpSocket->bind(QHostAddress::Any, 1111);
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readingData()));
}

Worker::~Worker()
{}

void Worker::setPath(QString fileWay)
{
	path = fileWay;
}

void Worker::getPort(int port)
{
	udpSocket->close();
	udpSocket->bind(QHostAddress::Any, port);
}

void Worker::stopSlot()
{
	udpSocket->close();
	times.clear();
}

void Worker::readingData()
{
	QHostAddress sender;
	quint16 senderPort;

	while (udpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		Info channelInfo;

		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

		channelNumber = datagram[6];
		ip = QHostAddress(sender.toIPv4Address()).toString();

		if (times.isEmpty())
		{
			SpeedTracker speedTracker(channelNumber, ip, int(senderPort));
			times.push_back(speedTracker);
			channelInfo.setDownloading(false);
			channelInfo.setDownloaded(0);//изначально у нас ничего не скачано и мы не скачиваем
		}
		else
		{
			bool flag = true;
			int j = 0;
			do
			{
				if ((times[j].ipNum() == ip) && (times[j].portNum() == int(senderPort)) && (times[j].channelNum() == channelNumber))
				{
					quint16 s16 = (static_cast<quint8>(datagram[2]) << 8) + static_cast<quint8>(datagram[3]);
					times[j].addData(s16);
					flag = false;
				}
				j++;
			} while (j < times.size());
			if (flag)
			{
				SpeedTracker speedTracker(channelNumber, ip, int(senderPort));
				times.push_back(speedTracker);
				channelInfo.setDownloading(false);
				channelInfo.setDownloaded(0);//изначально у нас ничего не скачано и мы не скачиваем
			}
		}

		channelInfo.setChannel(channelNumber);
		channelInfo.setIpSender(ip);

		int i = 0;
		do
		{
			if ((times[i].ipNum() == ip) && (times[i].portNum() == int(senderPort)) && (times[i].channelNum() == channelNumber))
			{
				channelInfo.setSpeed(times[i].speed() * 1000.0 / 1000.0 * 8);
			}
			i++;
		} while (i < times.size());

		QFile f(path);

		channelInfo.setPortSender(senderPort);
		channelInfo.setUdpPack(datagram);
		channelInfo.setDownloaded(float(f.size()) / float(1024));

		emit infoSend(channelInfo);
	}
}
