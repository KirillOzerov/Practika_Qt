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

int QTableModel::rowCount() const
{
	return dataInfo.size();
}

int QTableModel::columnCount(const QModelIndex& parent) const
{
	return 6 + 1;
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

Qt::ItemFlags QTableModel::flags(const QModelIndex& index) const
{
	if (index.column() == 6)
	{
		return QAbstractTableModel::flags(index) | Qt::ItemFlag::ItemIsUserCheckable;
	}

	return QAbstractTableModel::flags(index);
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
			return QVariant(QString::fromUtf8("Downloaded(kBait)"));
		case 6:
			return "Check";
		default:
			return QVariant();
		}
	}
	return QVariant();
}

bool QTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.column() == 6 && role == Qt::CheckStateRole)
	{
		dataInfo[index.row()].setDownloading(value == Qt::Checked);
	}

	return QAbstractTableModel::setData(index, value, role);
}

QVariant QTableModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		switch (index.column())
		{
			/*case 0:
				return dataInfo[index.row()].getDownloading();*/
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
	else if (role == Qt::CheckStateRole)
	{
		if (index.column() == 6)
			return dataInfo[index.row()].getDownloading() ? Qt::Checked : Qt::Unchecked;
	}
	return QVariant();
}

void QTableModel::clearWindow()
{
	auto i = index(0, 4);
	auto j = index(dataInfo.size() - 1, 4);
	dataInfo.clear();
	emit dataChanged(i, j);
	emit layoutChanged();
}

void QTableModel::addInfo(const Info& info)
{
	int i;
	for (i = 0; i < dataInfo.count(); i++)
	{
		Info& item = dataInfo[i];

		if ((item.getChannel() == info.getChannel()) && (item.getIpSender() == info.getIpSender()) && (item.getPortSender() == info.getPortSender()))
		{
			item.setSpeed(info.getSpeed());
			item.addToUdpPackage(info.getUdpPack());//добавление данных
			item.setDownloaded(info.getDownloaded());
			QModelIndex idx = index(0, 4);
			QModelIndex idx1 = index(dataInfo.size() - 1, 5);

			emit dataChanged(idx, idx1);
			break;
		}
	}

	if (i >= dataInfo.count())
	{
		insertRows(info);
		emit addCheckBoxSignal();
	}
}