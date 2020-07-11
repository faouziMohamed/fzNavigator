#ifndef PRINCIPALWIND_H
#define PRINCIPALWIND_H


#include <QMainWindow>
#include <QtWidgets>
#include <QWebEngineView>
#include <QTranslator>
#include <cstdarg>
#include "webEngineTools.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public slots:
    void addNewTab();
    void removeTab();
    void removeTab(int);
    void openNewWindow();
    void switchToAnOtherTab(int);
    void changeTheWindowTitle(QString);


  public:
    MainWindow(QWidget* parent);
    int numberOfTab();
    QWebEngineView* newTab();
    void closeThisWindow();
    ~MainWindow();


private:
    void setBehaviorForTabs();
    void createInitialTab();
    void applyAndFinalizeTabsConfigurationsToTheCentralView();
    bool currentActionIsNotNull(QAction *action);

    void creatingTheMenuFileShortcutAndConnection();
    void creatingTheMenuFileItems();
    void createMenu();
    void addMultipleActionsToTheMenu(QString name, QMenu *menuHeader, QList<QAction *> menuActions);
    void addMultipleActionsToTheMenu(QMenu *menuHeader, QList<QAction *> menuActions);
    void addMultipleActionsToTheMenu(QMenu *menuHeader,...);
    void createTheMenuFile();
    void createTheMenuNavigation();
    void createTheMenuHelp();
    WebEngineTools *newWebEngine(WebEngineTools *webEngineContainer);
    WebEngineTools *currentWindow();
    QWebEngineView *currentPage();

    QMenu *fileMenu;
      QAction *newWindowsAction;
      QAction *closeTabAction;
      QAction *exitAction;
      QAction *newTabAction;
    QMenu *navigationMenu;
    QMenu *helpMenu;


    QAction *m_previousAction;
    QAction *m_nextPageAction;
    QAction *m_refreshAction;
    QAction *m_stopAction;
    QAction *m_goAction;

    /*Inside the main windows*/
    QTabWidget *tabContainer;

};

#endif // PRINCIPALWIND_H
