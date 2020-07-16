#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QMainWindow>
#include <QtWidgets>
#include <cstdarg>
#include <QMap>
#include "FzGlobal.h"
#include "webPageView.h"
#include "webpage.h"
class TabWidget;

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
    void favIconSent(const QIcon& icon);
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
    void configureConnectionsForToolbarActions();
    void setUpOppeningWindow();
    QWidget *createWebPageLayout();
    void setUpCustomContexteMenu();
    void webViewConnections();
    void actionsConnections();


protected:
    const QString defaultHomePage = "http://duckduckgo.com/";
    QWebEngineProfile* m_Profile;
    WebPageView * webView;
    WebPage * webPage;
    QAction *m_urlIconAct;
    QMap<WebPage::WebAction, QAction*> toolbarAction;

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

    friend class TabWidget;
};

#endif // BROWSERTAB_H
