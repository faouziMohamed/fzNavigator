#ifndef PRINCIPALWIND_H
#define PRINCIPALWIND_H


#include <QMainWindow>
#include <QtWidgets>
#include <QWebEngineView>
#include <QTranslator>
#include "webEngineTools.h"

class PrincipalWind : public QMainWindow
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
    PrincipalWind(QWidget* parent);

    //QAction *
  private:
    void createShortcut();
    void createMenu();
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
    QAction *m_home;

    /*Inside the main windows*/
    QTabWidget *tabContainer;

};

#endif // PRINCIPALWIND_H
