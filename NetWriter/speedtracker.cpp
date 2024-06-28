#include "speedtracker.h"
#include <QDebug>

SpeedTracker::SpeedTracker(int channel, QString ip, int port)
{
	this->channel = channel;
	this->ip = ip;
	this->port = port;

	timeOfCreation = new QTime;
	timeOfCreation->start();

	this->totalSize = 0;
}

SpeedTracker::~SpeedTracker()
{}

int SpeedTracker::channelNum()
{
	return channel;
}

QString SpeedTracker::ipNum()
{
	return ip;
}

int SpeedTracker::portNum()
{
	return port;
}

void SpeedTracker::addData(int size)
{
	totalSize += size;
}

float SpeedTracker::speed()
{
	if (totalSize != 0)
	{
		float speed;
		if (timeOfCreation->elapsed() != 0)
		{
			speed = float(totalSize) / float(timeOfCreation->elapsed());
		}
		else
		{
			speed = float(totalSize) / float(1);
		}

		totalSize = 0;
		timeOfCreation->start();
		speeds.append(speed);
		float speedSum = 0;
		if (speeds.size() > 1)
		{
			int i = 0;
			do
			{
				speedSum += speeds[i];
				i++;
			} while (i < speeds.size());
		}
		else if (speeds.size() == 1)
		{
			float averageSpeed = speeds[0] / float(speeds.size());
			return averageSpeed;
		}
		if (speeds.size() == 500000)
		{
			speeds.erase(speeds.begin());
		};
		float averageSpeed = speedSum / float(speeds.length());
		return averageSpeed;
	}
	else
	{
		return 0;
	}
}
