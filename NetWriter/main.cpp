#include "netwriter.h"
#include "netreader.h"
#include <QtWidgets/QApplication>

#include <iostream>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetWriter w;
    NetReader r;

    qRegisterMetaType<Info>("Info");


    w.setWindowTitle("NetWriter");
    r.setWindowTitle("NetReader");
    r.show();
    w.show();
    return a.exec();
}
