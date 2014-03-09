#include <QApplication>
#include "mainwindow.h"
#include <string>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Rohatgi");
    app.setApplicationName("EncNotes");
    app.setOrganizationDomain("arohatgi.info");

    app.setWindowIcon(QIcon(":/icons/application-icon.png"));
    MainWindow m;
    if(app.arguments().length() == 2)
    {
        std::string openFileName = app.arguments().at(1).toStdString();
        m.openFile(openFileName);
    }
    m.setWindowIcon(QIcon(":/icons/application-icon.png"));
    m.show();

    return app.exec();
}
