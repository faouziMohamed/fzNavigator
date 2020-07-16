#ifndef TABWIDGETS_H
#define TABWIDGETS_H

#include <QtWidgets>
#include "webpage.h"
#include "webPageView.h"
#include "browsertab.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWebEngineProfile* profile, QWidget *parent=nullptr);
    QString themeDarkAurore();
public slots:
    void handleContextMenuRequested();
protected:
    BrowserTab* tab;
private:
    void setupTabsBehavior();
};

#endif // TABWIDGETS_H 
