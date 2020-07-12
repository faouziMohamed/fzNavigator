#include <QApplication>
#include "src/header/MainWindow.h"
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    locale = "fr";
    QTranslator translator;
    translator.load(QString(":/lang/fzNavigator_"+locale));
    app.installTranslator(&translator);

    MainWindow p(nullptr);

    p.showMaximized();
    return app.exec();
}
