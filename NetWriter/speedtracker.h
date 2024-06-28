#pragma once

#include <QObject>
#include <QTime>
#include <QVector>


class SpeedTracker : public QObject
{
	Q_OBJECT

public:
	SpeedTracker(int channel, QString ip, int port);
	~SpeedTracker();
	SpeedTracker(const SpeedTracker& rhs)
	{
		timeOfCreation = rhs.timeOfCreation;
		channel = rhs.channel;
		ip = rhs.ip;
		port = rhs.port;
		timeOfCreation = rhs.timeOfCreation;
		speeds = rhs.speeds;
		totalSize = rhs.totalSize;
	}

	int channelNum();
	QString ipNum();
	int portNum();

	void addData(int size);
	float speed();

	SpeedTracker& operator=(const SpeedTracker& rhs)
	{
		if (this == &rhs)
			return *this;
		timeOfCreation = rhs.timeOfCreation;
		channel = rhs.channel;
		ip = rhs.ip;
		port = rhs.port;
		timeOfCreation = rhs.timeOfCreation;
		totalSize = rhs.totalSize;
		speeds = rhs.speeds;
		return *this;
	}

private:
	QTime* timeOfCreation;

	QVector <int> speeds;

	int totalSize;

	int channel;
	QString ip;
	int port;
};
