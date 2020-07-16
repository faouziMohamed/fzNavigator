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
    QString themeDarkAurore(BrowserTab *btab);
        QString fznavName;
        QString newTabTitle;
signals:
    void customWindowTitleChanged(const QString &title);
public slots:
    //void handleContextMenuRequested();
    BrowserTab *addNewTab();
protected:
    BrowserTab* tab;
    QWebEngineProfile* m_profile;
    BrowserTab *currentTab();
    BrowserTab *widget(int index);
private:
    void setupTabsBehavior();
    void setUpTabConnexions(BrowserTab *newTab);
    void setUpMainConnexions();
};

#endif // TABWIDGETS_H 
