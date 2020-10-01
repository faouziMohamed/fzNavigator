#ifndef WebPageView_H
#define WebPageView_H

#include <QWidget>
#include <QAction>
#include <QWebEngineView>
#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>
#include "src/header/webpage.h"
#include "src/header/FzGlobal.h"
#include <functional>

typedef QList<QAction*>::const_iterator constIterator;
class BrowserTab;

class WebPageView : public QWebEngineView
{
    Q_OBJECT
public:
    WebPageView(QWidget *parent);

public:
    int progress() const;
    void setPage(WebPage *page);
    QIcon favIcon() const;

public slots:
    void initProgressBar();
    void pageOnLoad(int progress);
    void pageLodingIsFinished(bool succes);
    void setHomePage(const QString & url);
    const QString& homePage();
    //void newTabRequested();

signals:
    void favIconChanged(const QIcon &icon);
    void titleChanged(const QString &title);
    void devToolRequested(QWebEnginePage* page);
    void webActionChanged(WebPage::WebAction webAction,bool enabled);
    void shortcutActivated(WebPage::WebAction webAction,bool enabled);
    void findTextRequested(QAction* findText);
    void findSelectedTextRequested(QAction* findSelectedText);
    void linkTextRequested(const QString& text);
    void textSelected(const QString &text);
    
    void newFgTabRequested(BrowserTab*);
    void newBgTabRequested(BrowserTab*);
    void newWindowRequested(BrowserTab*);
    void newDialogRequested(WebPageView*);


protected:
   //static QMenu *contexteMenu;
   QString m_homePage ;
   
protected:
    WebPageView *createWindow(QWebEnginePage::WebWindowType type) override;
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
    void makeDefaultContexteMenuTranslatable();
    void findAndTranslate(WebPage::WebAction webAction);
};

#endif // WebPageView_H
