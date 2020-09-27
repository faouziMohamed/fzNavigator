#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>
#include <QtWebEngineWidgets>

class WebPageView;

class WebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    WebPage(QObject* parent=nullptr,
            QWebEngineProfile* profil = QWebEngineProfile::defaultProfile());

signals:
    void tabRequested(QString);            

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    //WebPage *createWindow(WebPage::WebWindowType type) override;
};

#endif // WEBPAGE_H
