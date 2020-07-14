#ifndef ENGINEVIEW_H
#define ENGINEVIEW_H

#include <QWidget>
#include <QAction>
#include <QWebEngineView>
typedef QList<QAction*>::const_iterator constIterator;
class EngineView : public QWebEngineView
{
    Q_OBJECT
public:
    EngineView(QWidget *parent);

public:
    int loadProgress() const;
    void setPage(QWebEnginePage *page);
public slots:
    void initProgressBar();
    void pageOnLoad(int progress);
    void pageLodingIsFinished(bool succes);

signals:
    void favIconChanged(const QIcon &icon);
    void titleChanged(const QString &title);
    void webActionEnabledChanged(QWebEnginePage::WebAction webAction,
                                 bool enabled);
protected:
    //QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);
    void contextMenuEvent(QContextMenuEvent *event) override;
    constIterator findAnAction(QAction *anAction, QList<QAction *> actions);
    constIterator findAnAction(QWebEnginePage::WebAction anAction, QList<QAction *> actions);
private:
    int m_progress;
    QWebEngineView *profile;
    QMenu* m_contexteMenu;
private:
    QMenu* newContexteMenu() const;
    void triggerWebActions();
    void configureEngineConnection();
    void createWebActionTrigger(QWebEnginePage *page, QWebEnginePage::WebAction webAction);
    void handleLoadProgress();
    void handlePageProperties();
    bool isActionInTheEnd(constIterator anAction, QList<QAction *> actions);
    void insertActionBefore(constIterator before, QAction *action, QMenu *menu);
    void insertInspectElementAction(QMenu *menu, QList<QAction *> actions);
};

#endif // ENGINEVIEW_H
