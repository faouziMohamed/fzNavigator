#include <QApplication>
#include "src/header/MainWindow.h"
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
    MainWindow p(nullptr);
    WebEngineTools w(0);
    BrowserTab tab(nullptr);
    //w.show();
    p.showMaximized();
    //tab.show();

    TabWidget browser(nullptr);
    //browser.show();
    return app.exec();
}
