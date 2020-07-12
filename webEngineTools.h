/**This class is used to wrap the web engine for every tab in the browser**/
#ifndef WEBENGINETOOLS_H
#define WEBENGINETOOLS_H

#define APPDIR QCoreApplication::applicationDirPath()
#include <QtWidgets>
#include <QTranslator>
#include <QMainWindow>
#include <QWebEngineView>

class WebEngineTools: public QMainWindow
{
  Q_OBJECT
  public slots:
    void changeUrl(QUrl);
    void changeTitle(QString);
    void initLoading();
    void loadUrl();
    void loading(int);
    void endOfLoad(bool);
    void changeIcon(const QIcon&);
    void previous();
    void next();
    void refresh();
    void goHome();
    void stop();

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

    void addActionsToTheToolbar(QToolBar *menuOfActions...);
    void insertActionInToTheToolbar();
    void initialiseMainToolbarAction();
    void insertURLFIeldInToTheToolbar();
    void linkToolbarActionsWithTheirIcons();

    void addToolbar();
    void addStatusBar();
    void addShortcut();
    QWidget *createWebPageLayout();
    QString preconfigureUrl(QString url);
    void configureEngineConnection();
    void configureURLField();
};
bool currentActionIsNotNull(QAction *action);

#endif // WEBENGINETOOLS_H
