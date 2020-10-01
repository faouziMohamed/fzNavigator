#ifndef TABWIDGETS_H
#define TABWIDGETS_H

#include <QtWidgets>
#include "webpage.h"
#include "webPageView.h"
#include "browsertab.h"
class TabsBehavior{
public:
    enum Tabs{
        NoNewTab      ,
        NewTab        ,
        CloseTab      ,
        closeAllTabs  ,
        ReloadAllTabs ,
        OnlyThisTab   ,
        ExceptThisTab
    };

};

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    enum Window{
        PinTab    = -2   ,
        UnPinTab         ,
        ForegroundTab    ,
        BackgroundTab    ,
        BrowserWindow    ,
        DialogWindow     ,
        DevToolWindow    ,
        DevToolBuiltin   ,
        SettingTab       ,
        SettingWindow    ,
        PrivateBuiltinTab,
        PrivateNewWindow ,
        ViewSourceTab
    };
    typedef BrowserTab* (TabWidget::*newWindowTab)(BrowserTab*);
    
public:
    TabWidget(QWebEngineProfile* profile
              , TabsBehavior::Tabs how=TabsBehavior::NewTab
              , QWidget *parent=nullptr
              );
    QString setUserTheme(const QString& cssFile);
        QString fznavName;
        QString newTabTitle;
signals:
    void customWindowTitleChanged(const QString &title);
public slots:
    //void handleContextMenuRequested();
    QWidget *addFirstTab(TabWidget::Window type=Window::ForegroundTab);
    QWidget *addNewTab(WebPageView *view = nullptr, 
                          TabWidget::Window type=Window::ForegroundTab);
    QWidget *addNewTab(BrowserTab *tab, Window type);
 
protected:
    BrowserTab* tab;
    QWebEngineProfile* m_profile;
    BrowserTab *currentTab();
    BrowserTab *tabAt(int index);
    void closeEvent(QCloseEvent *event);
    
private:
    void setupTabsBehavior();
    void setUpTabConnexions(BrowserTab *newTab);
    void setUpMainConnexions();
    BrowserTab *configureNewTab(BrowserTab *newTab);
    
    BrowserTab *newForeground(BrowserTab* newTab);
    BrowserTab *newBackgroundTab(BrowserTab* newTab);
    TabWidget  *newBrowserWindow(BrowserTab* window);
    WebPageView *newDialogWindow(WebPageView *pageView);
    BrowserTab *openDevToolWindow(BrowserTab* devTool);
    BrowserTab *openDevToolBuiltinTab(BrowserTab* devTool);
    BrowserTab *newPrivateTab(BrowserTab* privateTab);
    BrowserTab *newPrivateWindow(BrowserTab* windowTab);
};

#endif // TABWIDGETS_H 
