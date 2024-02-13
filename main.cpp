#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow gui;
    //app.setWindowIcon(QIcon(":/Resources/logo.png"));
    return app.exec();
}
