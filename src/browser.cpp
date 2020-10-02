#include "header/browser.h"

Browser::Browser(QWidget *parent) : QMainWindow(parent)
{
    //WebPageView p(nullptr);
    //p.setPage(new WebPage(&p));
    //p.load(QUrl("https://faouzimohamed.github.io/"));
    TabWidget *browser = new TabWidget(QWebEngineProfile::defaultProfile());
    //QHBoxLayout *centralLayout = new QHBoxLayout(this);
    //centralLayout->addWidget(browser);
    setCentralWidget(browser);
}
