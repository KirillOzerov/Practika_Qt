#include "netwriter.h"

#include <iostream>
#include <stdio.h>
#include <string.h>


NetWriter::NetWriter(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    timer = new QTimer(this);

    connect(ui.sendButton, &QPushButton::clicked, this, &NetWriter::sendButton_clicked);
    connect(this->timer, &QTimer::timeout, this, &NetWriter::send);
    connect(ui.stopButton, &QPushButton::clicked, this, &NetWriter::stopButton_clicked);
    connect(ui.sendOneButton, &QPushButton::clicked, this, &NetWriter::sendOneButton_clicked);

    udpSocket = new QUdpSocket(this);
}

NetWriter::~NetWriter()
{}

void NetWriter::sendButton_clicked() {
    timer->start(ui.lineEdit->text().toInt());
}

void NetWriter::stopButton_clicked() {
    timer->stop();
}

void NetWriter::sendOneButton_clicked() {
    send();
}

void NetWriter::send() {
    QByteArray msg;

    int size_start = 0;//минимальная длина тела пакета
    int size_end = 255;//максимальная длина тела пакета
    int size_l = rand() % (size_end - size_start + 1) + size_start;
    int size_b = rand() % (size_end - size_start + 1) + size_start;
    int size = 256 * size_b + size_l;
    msg.resize(size + 8);

    int channelNumber = ui.lineEdit_2->text().toInt();

    msg[0] = 0x5b;
    msg[1] = 0x5d;
    msg[2] = size_b;
    msg[3] = size_l;
    msg[4] = 0;
    msg[5] = 0;
    msg[6] = channelNumber;
    msg[7] = 0;


    char counter = 0;
    for (int i = 8; i < size; i++)
    {
        msg[i] = counter++;
    }

    udpSocket->writeDatagram(msg, QHostAddress::LocalHost, 1111);
}
