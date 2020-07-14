#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>
#include <QtWebEngineWidgets>
class WebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    WebPage(QObject* parent=nullptr,
            QWebEngineProfile* profil = QWebEngineProfile::defaultProfile()
            );
protected:
    void contextMenuEvent(QContextMenuEvent *event) ;
};

#endif // WEBPAGE_H
