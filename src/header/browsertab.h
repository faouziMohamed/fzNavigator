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
    void exitRequested();
    
protected:
    QString preconfigureUrl(QString url);
    void addWebPageView(QString url);
    BrowserTab *createNewWebPageView(QString url);
    void makeActionConnected(QPushButton *act, WebPage::WebAction webAction);

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
    void initializeActions();
    void configureURLField();
    void addBtnActions();
    void addURLField();
    void addOptionsMenu();
    void configureToolBar();
    void setUpActConnection();
    void addCustomContexteMenu();
    void configureWebPageView();
    void handleReceivedSignals();
    QWidget *addWebViewToLayout();
    QWidget *createWebPageLayout();
    void configContextMenu();
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

    void addOptions();
    
private:
    QToolBar  *m_toolbar;
    QPushButton *m_btnBack;
    QPushButton *m_btnNext;
    QPushButton *m_stop_relod;
    QPushButton *m_home;
    
    QAction *m_actBack;
    QAction *m_actNext;
    QAction *m_actStopReload;
    QAction *m_submit;
    QLineEdit *m_urlField;
    QProgressBar *m_progress;
    
    QToolButton* m_toolButton;
    QMenu* m_optionMenu;

    friend class TabWidget;
    void configOptionMenu();
};

#endif // BROWSERTAB_H
