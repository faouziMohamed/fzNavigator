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
    TabWidget* newBrowserinstance(TabWidget *browser=nullptr);

signals:
    
protected:
    void closeEvent(QCloseEvent *event) override;
    
private:
    TabWidget* instance;
    
    friend class TabWidget;
};

#endif // BROWSER_H
