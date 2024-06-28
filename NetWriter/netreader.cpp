#include "netreader.h"
#include "QTableModel.h"
#include "qtimer.h"

NetReader::NetReader(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	threadForWorker = new QThread();
	connect(this, SIGNAL(destroyed()), threadForWorker, SLOT(quit()));

	model = new QTableModel(this);
	ui.tableView->setModel(model);

	worker = new Worker();
	connect(worker, SIGNAL(infoSend(Info)), this, SLOT(receivingInfo(Info)));

	worker->moveToThread(threadForWorker);
	threadForWorker->start();

	connect(ui.startButton, &QPushButton::clicked, this, &NetReader::givePort);
	connect(this, SIGNAL(sendPort(int)), worker, SLOT(getPort(int)));
	connect(ui.stopButton, &QPushButton::clicked, this, &NetReader::sendStopSignal);
	connect(this, SIGNAL(stopSignal()), worker, SLOT(stopSlot()));
	connect(this, SIGNAL(stopSignal()), model, SLOT(clearWindow()));
}

NetReader::~NetReader()
{}

void NetReader::receivingInfo(Info info)
{
	addChannelInfo(info);
}

void NetReader::addChannelInfo(Info channelInfo)
{
	model->addInfo(channelInfo);
}

void NetReader::givePort()
{
	int port = ui.lineEdit->text().toInt();
	emit sendPort(port);
}

void NetReader::sendStopSignal()
{
	emit stopSignal();
}
