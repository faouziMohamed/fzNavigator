#ifndef ENGINEVIEW_H
#define ENGINEVIEW_H

#include <QWidget>
#include <QWebEngineView>

class EngineView : public QWebEngineView
{
    Q_OBJECT
public:
    EngineView(QWidget *parent);
    QWebEngineView * createWindow(QWebEnginePage::WebWindowType type) override;
};

#endif // ENGINEVIEW_H
