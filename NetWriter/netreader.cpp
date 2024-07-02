#include "netreader.h"
#include "QTableModel.h"
#include "qtimer.h"
#include "downloader.h"

NetReader::NetReader(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	threadForWorker = new QThread();
	connect(this, SIGNAL(destroyed()), threadForWorker, SLOT(quit()));
	threadForDownloader = new QThread();
	connect(this, SIGNAL(destroyed()), threadForWorker, SLOT(quit()));

	model = new QTableModel(this);
	ui.tableView->setModel(model);

	worker = new Worker();
	connect(worker, SIGNAL(infoSend(Info)), this, SLOT(receivingInfo(Info)));

	worker->moveToThread(threadForWorker);
	threadForWorker->start();

	downloader = new Downloader();

	downloader->moveToThread(threadForDownloader);
	threadForDownloader->start();

	connect(ui.startButton, &QPushButton::clicked, this, &NetReader::givePort);
	connect(this, SIGNAL(sendPort(int)), worker, SLOT(getPort(int)));
	connect(ui.stopButton, &QPushButton::clicked, this, &NetReader::sendStopSignal);
	connect(this, SIGNAL(stopSignal()), worker, SLOT(stopSlot()));
	connect(this, SIGNAL(stopSignal()), model, SLOT(clearWindow()));
	connect(ui.fileButton, SIGNAL(clicked()), this, SLOT(setFile()));
	connect(model, SIGNAL(addCheckBoxSignal()), this, SLOT(addCheckBox()));
}

NetReader::~NetReader()
{}

QString NetReader::fileWay()
{
	return path;
}

void NetReader::receivingInfo(Info info)
{
	addChannelInfo(info);
}

void NetReader::addChannelInfo(Info channelInfo)
{
	QByteArray usefullPart;
	quint16 s16 = (static_cast<quint8>(channelInfo.getUdpPack()[2]) << 8) + static_cast<quint8>(channelInfo.getUdpPack()[3]);
	usefullPart.resize(s16);
	for (int i = 8; i < (s16 + 8); i++)
	{
		usefullPart[i - 8] = channelInfo.getUdpPack()[i]; //здесь модифицировать массив данных(выбрать полезную нагрузку)
	}

	model->addInfo(channelInfo);
	downloader->addInfo(channelInfo, usefullPart);
}

void NetReader::addCheckBox()
{
	QCheckBox* wid = new QCheckBox();
	int row = model->rowCount() - 1;
	downloader->downloadFlags.append(false);

	connect(wid, &QCheckBox::stateChanged, this, [this, row](int checked)
		{
			dynamic_cast<QCheckBox*>(sender())->isChecked();
			if (checked == Qt::Checked)
			{
				downloader->downloadFlags[row] = true;
			}
			else
			{
				downloader->downloadFlags[row] = false;
			};

		});
	ui.tableView->setIndexWidget(model->index(model->rowCount() - 1, 0), wid);

}

void NetReader::givePort()
{
	int port = ui.lineEdit->text().toInt();
	emit sendPort(port);
}

void NetReader::sendStopSignal()
{
	emit stopSignal();
	downloader->downloadFlags.clear();
	downloader->cleanDataInfo();
	downloader->cleanUsefullParts();
}

void NetReader::setFile()
{
	QString fileWay;
	fileWay = QFileDialog::getOpenFileName(this, "Choose file", "C:/Users/k_Ozerov/Desktop", "txt files (*.txt)");
	ui.lineEdit_2->setText(fileWay);
	downloader->setPath(fileWay);
	worker->setPath(fileWay);
}
