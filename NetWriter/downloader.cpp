#include "downloader.h"

Downloader::Downloader()
{}

Downloader::~Downloader()
{}

void Downloader::addInfo(const Info& info, QByteArray usefullPart)
{
	bool flag = true;
	int i = 0;
	for (QVector<Info>::iterator iter = dataInfo.begin(); iter != dataInfo.end(); iter++)
	{
		if ((iter->getChannel() == info.getChannel()) && (iter->getIpSender() == info.getIpSender()) && (iter->getPortSender() == info.getPortSender()))
		{
			iter->addToUdpPackage(info.getUdpPack());

			if (downloadFlags[i] == true)
			{
				QFile f(path);
				f.open(QIODevice::Append);
				f.write(usefullPart);
				f.close();
			}
			flag = false;
		}
		i++;
	}
	if (flag)
	{
		dataInfo.append(info);

	}
}

void Downloader::setPath(QString fileWay)
{
	path = fileWay;
}

void Downloader::cleanDataInfo()
{
	dataInfo.clear();
}

void Downloader::cleanUsefullParts()
{
	usefullParts.clear();
}
