#ifndef PRINCIPALWIND_H
#define PRINCIPALWIND_H


#include <QMainWindow>
#include <QtWidgets>
#include <QWebEngineView>
#include <QTranslator>
#include "webEngineTools.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public slots:
    void addNewTab();
    void removeTab();
    void removeTab(int);
    void newWindow();
    void changeTab(int);
    void changeTitle(QString);


  public:
    MainWindow(QWidget* parent);
    ~MainWindow();

  private:
    void setBehaviorForTabs();
    void createInitialTab();
    void applyAndFinalizeTabsConfigurationsToTheCentralView();

    void creatingTheMenuFileShortcutAndConnection();
    void creatingTheMenuFileItems();
    void createMenu();
    void addActionToTheMenu(QString name, QMenu *menuHeader, QList<QAction *> menuActions);
    void createTheMenuFile();
    void createTheMenuNavigation();
    void createTheMenuHelp();
    WebEngineTools *currentWindow();
    QWebEngineView *currentPage();

    QMenu *fileMenu;
      QAction *newWindowsAction;
      QAction *closeTabAction;
      QAction *exitAction;
      QAction *newTabAction;
    QMenu *navigationMenu;
    QMenu *helpMenu;


    QAction *m_previous;
    QAction *m_nextPage;
    QAction *m_refresh;
    QAction *m_stop;
    QAction *m_go;

    /*Inside the main windows*/
    QTabWidget *tabContainer;

};

#endif // PRINCIPALWIND_H
