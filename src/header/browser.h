#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include "browsertab.h"
#include "tabwidget.h"


class Browser : public QMainWindow
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = nullptr);
    
signals:
    
};

#endif // BROWSER_H
