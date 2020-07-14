#ifndef TABWIDGETS_H
#define TABWIDGETS_H

#include <QtWidgets>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *parent=nullptr);
public slots:
    void handleContextMenuRequested(const QPoint &pos);
};

#endif // TABWIDGETS_H 
