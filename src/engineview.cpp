#include "header/engineview.h"
#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>
EngineView::EngineView(QWidget *parent)
    : QWebEngineView(parent)
    , m_progress(100)
{
    this->load(QUrl("http://duckduckgo.com/"));
    configureEngineConnection();
}

void EngineView::configureEngineConnection()
{
    handleLoadProgress();
    handlePageProperties();
}
void EngineView::handleLoadProgress()
{
    connect(this,SIGNAL(loadStarted()),this,SLOT(initProgressBar()));
    connect(this,SIGNAL(loadProgress(int)),this, SLOT(pageOnLoad(int)));
    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(pageLodingIsFinished(bool)));
}
void EngineView::handlePageProperties()
{
    connect(this,&QWebEngineView::iconChanged, [this](){emit favIconChanged(icon());});
    connect(this,&QWebEngineView::iconChanged, [this](){emit titleChanged(title());});
}

void EngineView::initProgressBar()
{
    m_progress = 0;
}
void EngineView::pageOnLoad(int progress)
{
    m_progress = progress;
}
void EngineView::pageLodingIsFinished(bool succes)
{
    m_progress = succes ? 100:-1;
}

void EngineView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = newContexteMenu();
    const QList<QAction *> actions = menu->actions();
    insertInspectElementAction(menu,actions);
    menu->popup(event->globalPos());
}
QMenu* EngineView::newContexteMenu() const
{
    return page()->createStandardContextMenu();
}
void EngineView::insertInspectElementAction(QMenu* menu, QList<QAction*> actions)
{
    auto inspectElement = findAnAction(QWebEnginePage::InspectElement,actions);
    auto viewSource = findAnAction(QWebEnginePage::ViewSource, actions);
    if (isActionInTheEnd(inspectElement,actions))
    {
        if (isActionInTheEnd(viewSource,actions)){menu->addSeparator();}
        QAction *action = new QAction("Inspect element", menu);
        insertActionBefore(inspectElement,action,menu);
    }
}

constIterator EngineView::findAnAction(QAction* anAction,QList<QAction*> actions)
{
    return  std::find(actions.cbegin(), actions.cend(),anAction);
}
constIterator EngineView::findAnAction(QWebEnginePage::WebAction anAction,
                              QList<QAction*> actions)
{
    return EngineView::findAnAction(page()->action(anAction),actions);
}
bool EngineView::isActionInTheEnd(constIterator anAction, QList<QAction*> actions)
{
    return anAction == actions.cend();
}
void EngineView::insertActionBefore(constIterator before, QAction* action,
                                                   QMenu* menu)
{
    QAction *beforeAction(*before);
    menu->insertAction(beforeAction, action);
}
int  EngineView::loadProgress() const
{return m_progress;}
void EngineView::setPage(QWebEnginePage *page)
{
    createWebActionTrigger(page,QWebEnginePage::Forward);
    createWebActionTrigger(page,QWebEnginePage::Back);
    createWebActionTrigger(page,QWebEnginePage::Reload);
    createWebActionTrigger(page,QWebEnginePage::Stop);
    QWebEngineView::setPage(page);
}
void EngineView::createWebActionTrigger(QWebEnginePage *page,
                                        QWebEnginePage::WebAction webAction)
{
    QAction *action = page->action(webAction);
    connect(action, &QAction::changed, [this, action, webAction]{
        emit webActionEnabledChanged(webAction, action->isEnabled());
    });
}





