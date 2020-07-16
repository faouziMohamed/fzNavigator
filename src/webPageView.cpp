#include "header/webPageView.h"

WebPageView::WebPageView(QWidget *parent)
    : QWebEngineView(parent)
    , m_progress(100)
{
    findSelectedText = new QAction(tr("Find selected text"),this);
    findSelectedText->setEnabled(false);
    this->load(QUrl("http://duckduckgo.com/"));
    setUpDefaultInnerConnection();
}

void WebPageView::setUpDefaultInnerConnection()
{
    handleLoadProgress();
    handlePageProperties();
}
void WebPageView::handleLoadProgress()
{
    connect(this,SIGNAL(loadStarted()),this,SLOT(initProgressBar()));
    connect(this,SIGNAL(loadProgress(int)),this, SLOT(pageOnLoad(int)));
    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(pageLodingIsFinished(bool)));
}
void WebPageView::handlePageProperties()
{
    connect(this,&QWebEngineView::iconChanged,[this](){emit favIconChanged(favIcon());});
    connect(this,&QWebEngineView::titleChanged, [this](){
        emit titleChanged(title());});
    connect(this,&QWebEngineView::selectionChanged,[this]{
            if(selectedText().isEmpty())
                {   findSelectedText->setEnabled(false);}
            else{   findSelectedText->setEnabled(true);
                    emit textSelected(selectedText());
                }
    });
}

void WebPageView::initProgressBar()
{
    m_progress = 0;
    emit favIconChanged(favIcon());
}
void WebPageView::pageOnLoad(int progress)
{
    m_progress = progress;
}
void WebPageView::pageLodingIsFinished(bool succes)
{
    m_progress = succes ? 100:-1;
    emit favIconChanged(favIcon());
}
/**
 * Override of the inherit function to diplay the contexte menu
*/
void WebPageView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = newContexteMenu();
    const QList<QAction *> actions = menu->actions();
    insertInspectElementAction(menu,actions);
    insertFindATextGroup(menu);
    insertCopyTextLink(menu);
    makeDefaultContexteMenuTranslatable();
    menu->popup(event->globalPos());

}
QMenu* WebPageView::newContexteMenu() const
{
    return page()->createStandardContextMenu();
}
void WebPageView::insertInspectElementAction(QMenu* menu, QList<QAction*> actions)
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
void WebPageView::insertFindATextGroup(QMenu* menu)
{
    QMenu* findGroupe = new QMenu(tr("Find"),this);
    menu->addSeparator();
    QAction* findText = new QAction(tr("Find text"),this);
    findGroupe->addAction(findText);
    findGroupe->addAction(findSelectedText);
    emitSignalIfTriggered(findText,findSelectedText);
    menu->addMenu(findGroupe);
}
void WebPageView::insertCopyTextLink(QMenu* menu)
{
    auto before = findAnAction(QWebEnginePage::CopyLinkToClipboard,
                               menu->actions());
    if(!isActionInTheEnd(before,menu->actions()))
    {
        QAction* copyLinkText = new QAction(tr("Copy link text"));
        insertActionBefore(before,copyLinkText,menu);
        connect(copyLinkText,&QAction::triggered,[this]{
            QString lintText = page()->contextMenuData().linkText();
            emit linkTextRequested(lintText);
        });
    }
}
void WebPageView::emitSignalIfTriggered(QAction* findText,QAction* findSelectedText)
{
    connect(findText,&QAction::triggered,[this,findText]{
        emit findTextRequested(findText);});
    connect(findSelectedText,&QAction::triggered,[this,findSelectedText]{
        emit findSelectedTextRequested(findSelectedText);});
}
constIterator WebPageView::findAnAction(QAction* anAction,QList<QAction*> actions)
{
    return  std::find(actions.cbegin(), actions.cend(),anAction);
}
constIterator WebPageView::findAnAction(WebPage::WebAction anAction,
                              QList<QAction*> actions)
{
    return WebPageView::findAnAction(page()->action(anAction),actions);
}
bool WebPageView::isActionInTheEnd(constIterator anAction, QList<QAction*> actions)
{
    return anAction == actions.cend();
}
void WebPageView::insertActionBefore(constIterator before, QAction* action,
                                                   QMenu* menu)
{
    QAction *beforeAction(*before);
    menu->insertAction(beforeAction, action);
}
void WebPageView::makeDefaultContexteMenuTranslatable()
{
    findAndTranslate(WebPage::Back);
    findAndTranslate(WebPage::Forward);
    findAndTranslate(WebPage::Reload);
    findAndTranslate(WebPage::Cut);
    findAndTranslate(WebPage::Paste);
    findAndTranslate(WebPage::Undo);
    findAndTranslate(WebPage::Redo);
    findAndTranslate(WebPage::SelectAll);
    findAndTranslate(WebPage::OpenLinkInThisWindow);
    findAndTranslate(WebPage::OpenLinkInNewWindow);
    findAndTranslate(WebPage::OpenLinkInNewTab);
    findAndTranslate(WebPage::OpenLinkInNewBackgroundTab);
    findAndTranslate(WebPage::CopyLinkToClipboard);
    findAndTranslate(WebPage::CopyImageToClipboard);
    findAndTranslate(WebPage::CopyImageUrlToClipboard);
    findAndTranslate(WebPage::CopyMediaUrlToClipboard);
    findAndTranslate(WebPage::DownloadLinkToDisk);
    findAndTranslate(WebPage::DownloadImageToDisk);
    findAndTranslate(WebPage::DownloadMediaToDisk);
    findAndTranslate(WebPage::InspectElement);
    findAndTranslate(WebPage::SavePage);
    findAndTranslate(WebPage::ViewSource);
    findAndTranslate(WebPage::ExitFullScreen);
    findAndTranslate(WebPage::ExitFullScreen);
    findAndTranslate(WebPage::ExitFullScreen);
    findAndTranslate(WebPage::ExitFullScreen);
    findAndTranslate(WebPage::ExitFullScreen);
}
void WebPageView::findAndTranslate(WebPage::WebAction webAction)
{
    QAction* act = pageAction(webAction);
    if(act!=nullptr)
    {
        auto text = Fz::tr(act);
        act->setText(text);
    }
}

int  WebPageView::progress() const
{return m_progress;}
void WebPageView::setPage(WebPage *page)
{
    setUpPageActionConnections(page);
    setUpPageActionShortcuts(page);
    QWebEngineView::setPage(page);
}

QIcon WebPageView::favIcon() const
{
    QIcon favIcon = icon();
    if (!favIcon.isNull())
        return favIcon;
    if (m_progress < 0) {
        static QIcon errorIcon(QIcon(":/fznavigator_icones/danger.svg"));
        return errorIcon;
    } else if (m_progress < 100) {
        static QIcon loadingIcon(QIcon(":/fznavigator_icones/loader.gif"));
        return loadingIcon;
    } else {
        static QIcon defaultIcon(QIcon(":/fznavigator_icones/web.png"));
        return defaultIcon;
    }
}
void WebPageView::setUpPageActionConnections(WebPage* page)
{
    setupConnexion(page,WebPage::Forward);
    setupConnexion(page,WebPage::Back);
    setupConnexion(page,WebPage::Reload);
    setupConnexion(page,WebPage::Stop);
}
void WebPageView::setUpPageActionShortcuts(WebPage* page)
{
    setUpShortcut(QKeySequence::Back,page,WebPage::Forward);
    setUpShortcut(QKeySequence::Forward,page,WebPage::Back);
    setUpShortcut(QKeySequence("CTRL+R"),page,WebPage::Reload);
    setUpShortcut(QKeySequence::Cancel,page,WebPage::Stop);
}
void WebPageView::setupConnexion(WebPage *page, WebPage::WebAction webAction)
{
    QAction *action = page->action(webAction);
    connect(action, &QAction::changed, [this, action, webAction]{
        emit webActionChanged(webAction, action->isEnabled());
    });
}
void WebPageView::setUpShortcut(QKeySequence seq,WebPage *page,
                               WebPage::WebAction webAction )
{
    QAction *action = page->action(webAction);
    action->setShortcut(seq);
    connect(new QShortcut(seq,this),&QShortcut::activated,[seq,this,action]{
        emit shortcutActivated(WebPage::Reload, action->isEnabled());});
}

