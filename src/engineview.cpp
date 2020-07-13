#include "header/engineview.h"

EngineView::EngineView(QWidget *parent):
    QWebEngineView(parent)
{
    this->load(QUrl("http://duckduckgo.com/"));
}

QWebEngineView *EngineView::createWindow(QWebEnginePage::WebWindowType type)
{
    QWebEngineView *p = new QWebEngineView();
    if(type == QWebEnginePage::WebBrowserWindow)
    {
        p->setUrl(this->url());
        p->show();
    }
    else{
        this->load(this->url());
    }
    return p;
}

