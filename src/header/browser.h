#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include "browsertab.h"
#include "tabwidget.h"

class Browser : public QMainWindow
{
    Q_OBJECT
public:
    Browser(QWidget *parent=nullptr, TabWidget* browserWindow=nullptr);

public slots:
    TabWidget* newInstance(TabWidget *browser=nullptr);

signals:
    
protected:
    void closeEvent(QCloseEvent *event) override;
    static int  count();
    static int  incrementNbInstances(Browser *instance);
    static int  decrementNbInstances(Browser *instance);
    static void removeInstance(Browser* instance);
    static void closeAllInstances();
    static void closeAllInstancesExcept(Browser* instance);
    static void closeAllInstancesExcept(int  instance_num);


protected:
    int instance_num;
    static int nb_instances;
    static QVector<Browser*> all_instances;
    
private:
    TabWidget* tabwidget_instance;
    
    friend class TabWidget;
};


#endif // BROWSER_H
