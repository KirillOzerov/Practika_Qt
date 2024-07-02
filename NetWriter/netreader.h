#pragma once

#include <QMainWindow>
#include "ui_netreader.h"
#include "Info.h"
#include "qudpsocket.h"
#include <random>
#include "worker.h"
#include <qthread.h>
#include <QFileDialog>
#include <QCheckBox>
#include <QVector>


class QTableModel;
class Downloader;

class NetReader : public QMainWindow
{
	Q_OBJECT

public:
	NetReader(QWidget* parent = nullptr);
	~NetReader();
	QString fileWay();

private:
	Ui::NetReaderClass ui;
	QTableModel* model;
	Worker* worker;
	QThread* threadForWorker;
	QThread* threadForDownloader;
	int time;
	QString path;
	Downloader* downloader;

public slots:
	void receivingInfo(Info info);
	void addChannelInfo(Info channelInfo);
	void addCheckBox();
	void givePort();
	void sendStopSignal();
	void setFile();
signals:
	void giveTime(int time);
	void sendPort(int port);
	void stopSignal();
};
