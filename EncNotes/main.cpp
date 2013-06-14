#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/application-icon.png"));
    MainWindow m;
    m.setWindowIcon(QIcon(":/icons/application-icon.png"));
    m.show();

    return app.exec();
}
