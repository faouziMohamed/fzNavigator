#ifndef ENGINEVIEW_H
#define ENGINEVIEW_H

#include <QWidget>
#include <QAction>
#include <QWebEngineView>
#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>
#include "src/header/webpage.h"

typedef QList<QAction*>::const_iterator constIterator;
class EngineView : public QWebEngineView
{
    Q_OBJECT
public:
    EngineView(QWidget *parent);

public:
    int loadProgress() const;
    void setPage(WebPage *page);
public slots:
    void initProgressBar();
    void pageOnLoad(int progress);
    void pageLodingIsFinished(bool succes);

signals:
    void favIconChanged(const QIcon &icon);
    void titleChanged(const QString &title);
    void devToolRequested(QWebEnginePage* page);
    void webActionChanged(WebPage::WebAction webAction,bool enabled);
    void findTextRequested(QAction* findText);
    void findSelectedTextRequested(QAction* findSelectedText);
    void linkTextRequested(const QString& text);
    void textSelected(const QString &text);

protected:
   //static QMenu *contexteMenu;
protected:
    //QWebEngineView *createWindow(WebPage::WebWindowType type);
    void contextMenuEvent(QContextMenuEvent *event) override;
    constIterator findAnAction(QAction *anAction, QList<QAction *> actions);
    constIterator findAnAction(WebPage::WebAction anAction, QList<QAction *> actions);
protected slots:
    void insertFindATextGroup(QMenu *menu);
private:
    int m_progress;
    QWebEngineProfile *profile;
    QMenu* m_contexteMenu;
    QAction *findSelectedText;
private:
    QMenu* newContexteMenu() const;
    void triggerWebActions();
    void setUpDefaultInnerConnection();
    void createWebActionTrigger(WebPage *page, WebPage::WebAction webAction);
    void handleLoadProgress();
    void handlePageProperties();
    bool isActionInTheEnd(constIterator anAction, QList<QAction *> actions);
    void insertActionBefore(constIterator before, QAction *action, QMenu *menu);
    void insertInspectElementAction(QMenu *menu, QList<QAction *> actions);
    void setupConnexion(WebPage *page, WebPage::WebAction webAction);
    void setUpPageActionConnections(WebPage *page);
    void setUpPageActionShortcuts(WebPage *page);
    void setUpShortcut(QKeySequence seq, WebPage *page, WebPage::WebAction webAction);
    void emitSignalIfTriggered(QAction *findText, QAction *findSelectedText);
    void insertCopyTextLink(QMenu *menu);
};

#endif // ENGINEVIEW_H
