#pragma once

#include <QtWidgets/QDialog>
#include "ui_netwriter.h"
#include <qtimer.h>
#include "qudpsocket.h"
#include <qthread.h>

class NetWriter : public QDialog
{
    Q_OBJECT

public:
    NetWriter(QWidget* parent = nullptr);
    ~NetWriter();

private:
    Ui::NetWriterClass ui;
    QUdpSocket* udpSocket;
    QTimer* timer;

public slots:
    void sendButton_clicked();
    void stopButton_clicked();
    void sendOneButton_clicked();
    void send();
};
