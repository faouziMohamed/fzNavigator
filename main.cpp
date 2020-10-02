#include <QApplication>
#include "src/header/browser.h"
#include <QTranslator>
#include <QTabWidget>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    //locale = "fr";
    QTranslator translator;
    translator.load(QString(":/lang/fzNavigator_fr"));
    app.installTranslator(&translator);
    //BrowserTab tab(nullptr);
    //tab.show();
    Browser b(nullptr);
    b.show();
    return app.exec();
}
