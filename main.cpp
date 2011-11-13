#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow QTGUI_Writer;
    QTGUI_Writer.show();

    return a.exec();
}
