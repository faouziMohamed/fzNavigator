#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include "browsertab.h"
#include "tabwidget.h"
#include "FzGlobal.h"

class Browser : public QMainWindow
{
    Q_OBJECT
public:
    Browser(TabWidget* browserWindow, QWidget *parent=nullptr);
    Browser();
    
public slots:
    TabWidget* newInstance(TabWidget *browser=nullptr);

signals:
    
protected:
    void closeEvent(QCloseEvent *event) override;
    static int  count();
    static int  addInstance(Browser *instance);
    static int  removeInstance(Browser *instance);
    static void deleteInstance(Browser* instance);
    static void closeAllInstances();
    static void closeAllInstancesExcept(Browser* instance);
    static void closeAllInstancesExcept(int  instance_num);

protected:
    static QVector<Browser*> all_instances;
    
private:
    TabWidget* tabwidget_instance;
    friend class TabWidget;
    void configureWindow();
};


#endif // BROWSER_H
