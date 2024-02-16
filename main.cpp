#include "./gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.setWindowIcon(QIcon(":/Resources/logo.png"));

    return a.exec();
}
