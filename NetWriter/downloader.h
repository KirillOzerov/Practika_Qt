#pragma once

#include <QObject>
#include "info.h"
#include "netreader.h"
#include <QString>

class Downloader : public QObject
{
	Q_OBJECT

public:
	Downloader();
	~Downloader();
	void addInfo(const Info& info, QByteArray usefullPart);
	void setPath(QString fileWay);
	void cleanDataInfo();
	void cleanUsefullParts();
	QVector <bool> downloadFlags;
private:
	QVector<Info> dataInfo;
	QVector<QByteArray> usefullParts;
	QString path;
};
