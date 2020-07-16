#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QMainWindow>
#include <QtWidgets>
#include <cstdarg>
#include <QMap>
#include "FzGlobal.h"
#include "webPageView.h"
#include "webpage.h"

class BrowserTab : public QMainWindow
{
    Q_OBJECT
public:
    explicit BrowserTab(QWidget *parent
                        , QWebEngineProfile *profile = new QWebEngineProfile
                        , QString url="");

    WebPageView *view();
    WebPage* page();


signals:
        void loadProgress(int progress);
protected:
    const QString defaultHomePage = "http://duckduckgo.com/";
    QWebEngineProfile* m_Profile;
    WebPageView * webView;
    WebPage * webPage;
    QMap<WebPage::WebAction, QAction*> toolbarAction;
protected:
    QString preconfigureUrl(QString url);
    void insertWebPageView(QString url);
    BrowserTab *createNewWebPageView(QString url);
    void makeActionConnected(QAction *act, WebPage::WebAction webAction);
public slots:
    void ShowContextMenu(const QPoint &pos);
    void loadUrl();
    void goToHomePage();
    void handleCurrentChanged(QWebEnginePage::WebAction webAct, bool state);
    void handleLoadProgress(int progress);
    void handleWebActionChanged(WebPage::WebAction webAct, bool state);

private:
    QToolBar  *m_toolbar;
    QAction   *m_backHistoryAction;
    QAction   *m_nextHistoryAction;
    QAction   *m_stopReloadAction;
    QAction   *m_homeAction;
    QAction   *m_submit;
    QLineEdit *m_urlField;
    QProgressBar *m_progress;
    QList<QAction*> separators;

private:
    void addToolbar();
    void addStatusBar();
    void initializeMainToolbarAction();
    void configureURLField();
    void insertActionInToTheToolbar();
    void addActionsToTheToolbar(QToolBar *aToolbar...);
    void insertURLFIeldInToTheToolbar();
    void linkToolbarActionsWithTheirIcons();
    void setToolBarBehavior();
    void configureToolbarActionsShortcuts();
    void configureToolbarActionsConnections();
    void setUpOppeningWindow();
    QWidget *createWebPageLayout();

    friend class TabWidget;
    void setUpCustomContexteMenu();
};

#endif // BROWSERTAB_H
