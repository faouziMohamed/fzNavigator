#include "header/browsertab.h"

BrowserTab::BrowserTab(QWidget *parent, QWebEngineProfile *profile, QString url)
    : QMainWindow(parent)
    , m_Profile(profile)
{
    insertWebPageView(url);
    addToolbar();
    addStatusBar();
    configureOppeningWindowSize();
    setUpCustomContexteMenu();
}

void BrowserTab::setUpCustomContexteMenu()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}
WebPageView* BrowserTab::view()
{
    return webView;
}
WebPage *BrowserTab::page()
{
    return webPage;
}
void BrowserTab::addToolbar()
{
    initializeMainToolbarAction();
    configureURLField();
    insertActionInToTheToolbar();
    insertURLFIeldInToTheToolbar();
    linkToolbarActionsWithTheirIcons();
    configureToolbarActionsConnections();
    setToolBarBehavior();
}

void BrowserTab::setToolBarBehavior()
{
    m_toolbar->setMovable(false);
    m_toolbar->setFloatable(false);
    m_toolbar->toggleViewAction()->setVisible(false);
}
void BrowserTab::addStatusBar()
{
    m_progress = new QProgressBar;
    m_progress->reset();
    m_progress->setVisible(false);
    statusBar()->addWidget(m_progress,1);
    statusBar()->setVisible(true);
}

void BrowserTab::configureToolbarActionsConnections()
{
    makeActionConnected(m_backHistoryAction,WebPage::Back);
    makeActionConnected(m_nextHistoryAction,WebPage::Forward);
    makeActionConnected(m_reloadAction,WebPage::Reload);
    makeActionConnected(m_stopAction,WebPage::Stop);
    connect(webView,&WebPageView::shortcutActivated,
            webView,&WebPageView::triggerPageAction);
    connect(m_submit,&QAction::triggered,[this]{loadUrl();});
    connect(m_urlField,&QLineEdit::returnPressed,[this]{loadUrl();});
    connect(new QShortcut(QKeySequence("CTRL+L"),this),
            &QShortcut::activated,[this]{
            m_urlField->selectAll();
            m_urlField->setFocus(Qt::OtherFocusReason);});
    connect(webView,&WebPageView::webActionChanged,this,
                    &BrowserTab::handleCurrentChanged);
}


void BrowserTab::handleCurrentChanged(WebPage::WebAction webAct, bool state)
{


    //emit loadProgress(webView->progress());
    toolbarAction.value(webAct)->setEnabled(state);
    /*
    if (index != -1)
    {
        WebPageView *view = webView;
        if (!view->url().isEmpty())
            view->setFocus();
        //emit titleChanged(view->title());
        //emit urlChanged(view->url());
        //emit favIconChanged(view->favIcon());
        emit view->webActionChanged(WebPage::Back, webPage->action(QWebEnginePage::Back)->isEnabled());
        emit view->webActionChanged(WebPage::Forward, webPage->action(QWebEnginePage::Forward)->isEnabled());
        emit view->webActionChanged(WebPage::Stop, webPage->action(QWebEnginePage::Stop)->isEnabled());
        emit view->webActionChanged(WebPage::Reload,webPage->action(QWebEnginePage::Reload)->isEnabled());
    } else {
        //emit titleChanged(QString());
        emit loadProgress(0);
        //emit urlChanged(QUrl());
        //emit favIconChanged(QIcon());
        emit webView->webActionChanged(WebPage::Back, false);
        emit webView->webActionChanged(QWebEnginePage::Forward, false);
        emit webView->webActionChanged(QWebEnginePage::Stop, false);
        emit webView->webActionChanged(QWebEnginePage::Reload, true);
    }*/

}

void BrowserTab::startOfLoading()
{qDebug()<<"Start"<<endl;
    m_progress->reset();
    m_progress->setValue(0);
    m_progress->setVisible(true);
}
void BrowserTab::loadProgressing(int value)
{
    if(m_progress->value()<0)
        return;
    m_progress->setValue(value);
    m_reloadAction->setVisible(false);
    m_stopAction->setVisible(true);
    qDebug()<<"Loading " <<m_progress->value()<<endl;
}
void BrowserTab::endOfLoading(bool visible)
{
    if(visible)
    {
        qDebug()<<"Finish"<<endl;
        m_progress->setVisible(false);
        m_progress->setValue(-1);
        statusBar()->showMessage(tr("Ready"),3000);
        m_stopAction->setVisible(false);
        m_reloadAction->setVisible(true);
    }
}
void BrowserTab::makeActionConnected(QAction* act, WebPage::WebAction webAction)
{
    connect(act,&QAction::triggered,[this,webAction]{
             webView->triggerPageAction(webAction);});
}
void BrowserTab::configureOppeningWindowSize()
{
    this->resize(1024,650);
}
void BrowserTab::insertWebPageView(QString url)
{
    if(url.isEmpty ()){
        url = defaultHomePage;
    }
    createNewWebPageView(url);
}
BrowserTab *BrowserTab::createNewWebPageView(QString url)
{
    createWebPageLayout();
    url = preconfigureUrl(url);
    webView->load(QUrl(url));
    //configureEngineConnection();
    return this;
}

QWidget* BrowserTab::createWebPageLayout()
{
    QWidget *centralWidget = new QWidget(this);
    webView = new WebPageView(this);
    webPage = new WebPage(webView);
    webView->setPage(webPage);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(webView);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setDocumentMode(true);
    setCentralWidget(centralWidget);
    return centralWidget;
}
void BrowserTab::initializeMainToolbarAction()
{
    m_toolbar =  this->addToolBar(tr("Navigation"));
    m_backHistoryAction = new QAction(tr("Previous page"));
    m_nextHistoryAction     = new QAction(tr("Next Page"));
    m_reloadAction      = new QAction(tr("Refresh"));
    m_stopAction         = new QAction(tr("Stop"));
    m_homeAction         = new QAction(tr("Home"));
    m_submit             = new QAction(tr("Go"));

    m_backHistoryAction->setEnabled(false);
    m_nextHistoryAction->setEnabled(false);
    toolbarAction.insert(WebPage::Back,m_backHistoryAction);
    toolbarAction.insert(WebPage::Forward,m_nextHistoryAction);
    toolbarAction.insert(WebPage::Reload,m_reloadAction);
    toolbarAction.insert(WebPage::Stop,m_stopAction);
}

void BrowserTab::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("Context menu"), this);

   QAction action1("Remove Data Point", this);
   connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
   contextMenu.addAction(&action1);

   contextMenu.exec(mapToGlobal(pos));
}
void BrowserTab::configureURLField()
{
    m_urlField = new QLineEdit(defaultHomePage);
    m_urlField->setFocus(Qt::OtherFocusReason);
    m_urlField->setClearButtonEnabled(true);
}

void BrowserTab::insertActionInToTheToolbar()
{
    addActionsToTheToolbar(m_toolbar, m_backHistoryAction, m_nextHistoryAction,
                           m_reloadAction, m_stopAction, m_homeAction,nullptr);
    m_toolbar->insertSeparator(m_homeAction);
}
void BrowserTab::insertURLFIeldInToTheToolbar()
{
    m_toolbar->addWidget(m_urlField);
    m_toolbar->addAction(m_submit);
}
void BrowserTab::linkToolbarActionsWithTheirIcons()
{
    m_backHistoryAction->setIcon(QIcon(":/fznavigator_icones/prev.png"));
        m_nextHistoryAction->setIcon(QIcon(":/fznavigator_icones/next.png"));
         m_reloadAction->setIcon(QIcon(":/fznavigator_icones/refresh.png"));
            m_homeAction->setIcon(QIcon(":/fznavigator_icones/home.png"));
            m_stopAction->setIcon(QIcon(":/fznavigator_icones/stop.png"));
                m_submit->setIcon(QIcon(":/fznavigator_icones/go.png"));
}

void BrowserTab::addActionsToTheToolbar(QToolBar* aToolbar,...)
{
    va_list listOfvariableArguments;
    va_start(listOfvariableArguments, aToolbar);
    QAction *currentAction = va_arg(listOfvariableArguments, QAction *);
    while(Fz::currentActionIsNotNull(currentAction))
    {
        aToolbar->addAction(currentAction);
        currentAction = va_arg(listOfvariableArguments, QAction *);
    }
    va_end(listOfvariableArguments);
}



void BrowserTab::loadUrl()
{
    QString url = this->m_urlField->text();
    url = preconfigureUrl(url);
    webView->load(QUrl(url));
    //this->m_icon = QIcon();
}
void BrowserTab::previousPage()
{
    webView->back();
}
void BrowserTab::nextPage()
{
    webView->forward();
}
void BrowserTab::refreshPage()
{
    webView->reload();
}
void BrowserTab::goToHomePage()
{
   webView->load(QUrl(defaultHomePage));
}

QString BrowserTab::preconfigureUrl(QString url)
{
    url = url.replace('%',"%25");
    if(url.isEmpty())
    {
        url = "https:// ";
        return url;
    }

    if( (url.left(7) != "http://") && (url.left(8) != "https://" ) )
    {
        if(Fz::isNotAnUrlSyntaxe(url))
           url = "http://duckduckgo.com/?q="+url.replace(' ','+');
        else
           url = "http://"+url;
    }
    return url;
}
