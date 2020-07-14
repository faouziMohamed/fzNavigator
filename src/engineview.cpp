#include "header/engineview.h"

EngineView::EngineView(QWidget *parent)
    : QWebEngineView(parent)
    , m_progress(100)
{
    this->load(QUrl("http://duckduckgo.com/"));
    setUpDefaultInnerConnection();
}

void EngineView::setUpDefaultInnerConnection()
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
/**
 * Override of the inherit function to diplay the contexte menu
*/
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
    auto inspectElement = findAnAction(WebPage::InspectElement,actions);
    auto viewSource = findAnAction(WebPage::ViewSource, actions);
    if (isActionInTheEnd(inspectElement,actions))
    {
        if (isActionInTheEnd(viewSource,actions)){menu->addSeparator();}
        QAction *action = new QAction("Inspect element", menu);
        insertActionBefore(inspectElement,action,menu);
        connect(action,&QAction::triggered,[this](){emit devToolRequested(page());});
    }
}

constIterator EngineView::findAnAction(QAction* anAction,QList<QAction*> actions)
{
    return  std::find(actions.cbegin(), actions.cend(),anAction);
}
constIterator EngineView::findAnAction(WebPage::WebAction anAction,
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
void EngineView::setPage(WebPage *page)
{
    setUpPageActionConnections(page);
    setUpPageActionShortcuts(page);
    QWebEngineView::setPage(page);
}
void EngineView::setUpPageActionConnections(WebPage* page)
{
    setupConnexion(page,WebPage::Forward);
    setupConnexion(page,WebPage::Back);
    setupConnexion(page,WebPage::Reload);
    setupConnexion(page,WebPage::Stop);
}
void EngineView::setUpPageActionShortcuts(WebPage* page)
{
    setUpShortcut(QKeySequence::Back,page,WebPage::Forward);
    setUpShortcut(QKeySequence::Forward,page,WebPage::Back);
    setUpShortcut(QKeySequence("CTRL+R"),page,WebPage::Reload);
    setUpShortcut(QKeySequence::Cancel,page,WebPage::Stop);
}
void EngineView::setupConnexion(WebPage *page, WebPage::WebAction webAction)
{
    QAction *action = page->action(webAction);
    connect(action, &QAction::changed, [this, action, webAction]{
        emit webActionChanged(webAction, action->isEnabled());});
}
void EngineView::setUpShortcut(QKeySequence seq,WebPage *page,
                               WebPage::WebAction webAction )
{
    QAction *action = page->action(webAction);
    action->setShortcut(seq);
    connect(new QShortcut(seq,this),&QShortcut::activated,[this,action]{
        emit webActionChanged(WebPage::Reload, action->isEnabled());});
}


