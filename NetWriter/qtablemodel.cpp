#include "qtablemodel.h"
#include "netreader.h"

QTableModel::QTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{}

QTableModel::~QTableModel()
{}

int QTableModel::rowCount(const QModelIndex& parent) const
{
	return dataInfo.size();
}

int QTableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

bool QTableModel::insertRows(const Info& info, const QModelIndex& parent)
{
	beginInsertRows(parent, rowCount(parent), rowCount(parent));
	dataInfo.append(info);
	endInsertRows();
	return true;
}

bool QTableModel::removeRows(int position, const QModelIndex& parent)
{
	beginRemoveRows(parent, position, position);
	dataInfo.remove(position);
	endRemoveRows();
	return true;
}

QVariant QTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}
	if (orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return QVariant(QString::fromUtf8("Downloading"));
		case 1:
			return QVariant(QString::fromUtf8("SenderIP"));
		case 2:
			return QVariant(QString::fromUtf8("SenderPort"));
		case 3:
			return QVariant(QString::fromUtf8("Channel"));
		case 4:
			return QVariant(QString::fromUtf8("Speed(kBit/sec)"));
		case 5:
			return QVariant(QString::fromUtf8("Downloaded"));
		default:
			return QVariant();
		}
	}
	return QVariant();
}

QVariant QTableModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		switch (index.column())
		{
		case 0:
			return dataInfo[index.row()].getDownloading();
		case 1:
			return dataInfo[index.row()].getIpSender();
		case 2:
			return dataInfo[index.row()].getPortSender();
		case 3:
			return dataInfo[index.row()].getChannel();
		case 4:
			return dataInfo[index.row()].getSpeed();
		case 5:
			return dataInfo[index.row()].getDownloaded();
		}
	}
	return QVariant();
}

void QTableModel::clearWindow()
{
	auto i = index(int(dataInfo.begin()), 4);
	auto j = index(int(dataInfo.end()), 4);
	dataInfo.clear();
	emit dataChanged(i, j);
	emit layoutChanged();
}

void QTableModel::addInfo(const Info& info)
{
	bool flag = true;
	auto i = index(int(dataInfo.begin()), 4);
	auto j = index(int(dataInfo.end()), 4);
	for (QVector<Info>::iterator iter = dataInfo.begin(); iter != dataInfo.end(); iter++)
	{
		if ((iter->getChannel() == info.getChannel()) && (iter->getIpSender() == info.getIpSender()) && (iter->getPortSender() == info.getPortSender()))
		{
			iter->setSpeed(info.getSpeed());
			flag = false;
		}
	}
	emit dataChanged(i, j);
	if (flag)
	{
		insertRows(info);
	}
}