#include <QApplication>
#include "src/header/browsertab.h"
#include "src/header/tabwidget.h"
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
    BrowserTab tab(nullptr);
    //tab.show();

    TabWidget browser(QWebEngineProfile::defaultProfile());
    browser.show();
    return app.exec();
}
