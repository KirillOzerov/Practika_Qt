#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "info.h"
#include "netreader.h"
#include <vector>

class QTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	QTableModel(QObject* parent);
	~QTableModel();

	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	bool insertRows(const Info& info, const QModelIndex& parent = QModelIndex());
	bool removeRows(int position, const QModelIndex& parent = QModelIndex());
	QVariant headerData(int section, Qt::Orientation orientetion, int role) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
	void addInfo(const Info& info);
	void clearWindow();

private:
	QVector<Info> dataInfo;
};