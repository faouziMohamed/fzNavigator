#ifndef TABWIDGETS_H
#define TABWIDGETS_H

#include <QtWidgets>
#include "src/header/webpage.h"
#include "src/header/webPageView.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWebEngineProfile* profil, QWidget *parent=nullptr);
public slots:
    void handleContextMenuRequested();
};

#endif // TABWIDGETS_H 
