#pragma once

#include <QMainWindow>
#include "ui_netreader.h"
#include "Info.h"
#include <random>
#include "worker.h"
#include <qthread.h>


class QTableModel;

class NetReader : public QMainWindow
{
	Q_OBJECT

public:
	NetReader(QWidget* parent = nullptr);
	~NetReader();
private:
	Ui::NetReaderClass ui;
	QTableModel* model;
	Worker* worker;
	QThread* threadForWorker;
	int time;

public slots:
	void receivingInfo(Info info);
	void addChannelInfo(Info channelInfo);
	void givePort();
	void sendStopSignal();
signals:
	void giveTime(int time);
	void sendPort(int port);
	void stopSignal();
};
