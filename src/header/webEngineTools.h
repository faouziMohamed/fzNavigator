/**This class is used to wrap the web engine for every tab in the browser**/
#ifndef WEBENGINETOOLS_H
#define WEBENGINETOOLS_H

#define APPDIR QCoreApplication::applicationDirPath()
#include <QtWidgets>
#include <QTranslator>
#include <QMainWindow>
#include <QWebEngineView>
#include "FzGlobal.h"

class WebEngineTools: public QMainWindow
{
  Q_OBJECT
  public slots:
    void changeUrl(QUrl);
    void changeThisWindowTitle(QString);
    void loadUrl();
    void atTheStartOfPageLoading();
    void whilePageIsLoading(int);
    void atTheEndOfPageLoading(bool);
    void changeWindowFavcon(const QIcon&);
    void previousPage();
    void nextPage();
    void refreshPage();
    void goToHomePage();
    void stopPageLoading();

  public:


    WebEngineTools(QWidget *parent, QString url="");
    ~WebEngineTools();

    WebEngineTools* newPage(QString url);
    const QIcon &icon() {return m_icon ;}
    QString &title(){return m_title;}
    QWebEngineView *getWebEngine();

private:
    QString const defaultHomePage = "http://www.duckduckgo.com/";
    QString         m_title;
    QIcon           m_icon;
    QWebEngineView *m_webPage;
    QToolBar       *m_toolbar;
    QAction        *m_homeAction;
    QAction        *m_submit;
    QLineEdit      *m_urlField;
    QAction        *m_previousPageAction;
    QAction        *m_nextPageAction;
    QAction        *m_refreshAction;
    QAction        *m_stopAction;
    QProgressBar   *m_progress;

    void addToolbar();
    void addStatusBar();
    void configureToolbarActionsShortcuts();
    void configureToolbarActionsConnections();
    void configureOppeningWindowSize();
    void initialURLLoad(QString url);

    void addActionsToTheToolbar(QToolBar *menuOfActions...);
    void insertActionInToTheToolbar();
    void initializeMainToolbarAction();
    void insertURLFIeldInToTheToolbar();
    void linkToolbarActionsWithTheirIcons();

    QWidget *createWebPageLayout();
    QString preconfigureUrl(QString url);
    void configureEngineConnection();
    void configureURLField();
};
#endif // WEBENGINETOOLS_H
