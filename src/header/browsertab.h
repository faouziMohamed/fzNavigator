#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QMainWindow>
#include <QtWidgets>
#include <cstdarg>
#include <QMap>
#include "FzGlobal.h"
#include "webPageView.h"
#include "webpage.h"
#include "webPageView.h"

class TabWidget;

class BrowserTab : public QMainWindow
{
    Q_OBJECT
public:
    BrowserTab(QWidget *parent
              , QWebEngineProfile *profile
              , WebPageView *view=nullptr
              , QString url="");
    WebPageView *view();
    WebPage* page();
    void setView(WebPageView* view);
    const QString &defaultHomePage();

signals:
    void loadProgress(int progress);
    void favIconSent(const QIcon& icon);
    void newFgTabRequired(BrowserTab*);
    void newBgTabRequired(BrowserTab*);
    void newWindowTabRequired(BrowserTab*);
    void newDialogTabRequired(WebPageView*);
    
protected:
    QString preconfigureUrl(QString url);
    void insertWebPageView(QString url);
    BrowserTab *createNewWebPageView(QString url);
    void makeActionConnected(QAction *act, WebPage::WebAction webAction);

public slots:
    void ShowContextMenu(const QPoint &pos);
    void loadUrl();
    void goToHomePage();
    void emitProgress();
    void handleLoadProgress(int progress);
    void handleWebActionChanged(WebPage::WebAction webAct, bool state);
    void closeEvent(QCloseEvent *event) override;

private:
    void addToolbar();
    void addStatusBar();
    void initializeMainToolbarAction();
    void configureURLField();
    void addActionsInTheToolbar();
    void addURLFieldToTheToolbar();
    void linkToolbarActionsWithTheirIcons();
    void setUpToolBarBehavior();
    void setUpConnectionsForToolbarActions();
    void addCustomContexteMenu();
    void configureWebPageView();
    void handleReceivedSignals();
    QWidget *addWebViewToLayout();
    QWidget *createWebPageLayout();
    void setUpCustomContexteMenu();
    void webViewConnections();
    void actionsConnections();

public:

protected:
    QString m_defaultHomePage = "https://duckduckgo.com/";
    QWebEngineProfile* m_Profile;
    WebPageView * webView;
    WebPage * webPage;
    QAction *m_url_field_favIconAct;
    QMap<WebPage::WebAction, QAction*> toolbarAction;

private:
    QToolBar  *m_toolbar;
    QAction   *m_back;
    QAction   *m_next;
    QAction   *m_stop_relod;
    QAction   *m_home;
    QAction   *m_submit;
    QLineEdit *m_urlField;
    QProgressBar *m_progress;

    friend class TabWidget;
};

#endif // BROWSERTAB_H
