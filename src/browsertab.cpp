#include "header/browsertab.h"
#include "header/tabwidget.h"

BrowserTab::BrowserTab(QWidget *parent, QWebEngineProfile *profile, QString url)
    : QMainWindow(parent)
    , m_Profile(profile)
{
    insertWebPageView(url);
    addToolbar();
    addStatusBar();
    setUpOppeningWindow();
}

/*Fucntion called in the Constructor */
void BrowserTab::insertWebPageView(QString url)
{
    if(url.isEmpty ()){
        url = defaultHomePage;
    }
    createNewWebPageView(url);
}
void BrowserTab::addToolbar()
{
    initializeMainToolbarAction();
    configureURLField();
    insertActionInToTheToolbar();
    insertURLFIeldInToTheToolbar();
    linkToolbarActionsWithTheirIcons();
    configureConnectionsForToolbarActions();
    setToolBarBehavior();
}
void BrowserTab::addStatusBar()
{
    m_progress = new QProgressBar;
    m_progress->reset();
    m_progress->setVisible(false);
    statusBar()->addWidget(m_progress,1);
    statusBar()->setVisible(true);
}
void BrowserTab::setUpOppeningWindow()
{
    setUpCustomContexteMenu();
    this->resize(1024,650);
}

BrowserTab *BrowserTab::createNewWebPageView(QString url)
{
    createWebPageLayout();
    url = preconfigureUrl(url);
    webView->load(QUrl(url));
    //configureEngineConnection();
    return this;
}
/*Function called in the function addToolbar*/
void BrowserTab::initializeMainToolbarAction()
{
    m_toolbar =  this->addToolBar(tr("Navigation"));
    m_backHistoryAction = new QAction(tr("Previous page"));
    m_nextHistoryAction = new QAction(tr("Next Page"));
    m_stopReloadAction  = new QAction(this);
    m_homeAction        = new QAction(tr("Home"));
    m_submit            = new QAction(tr("Go"));

    m_backHistoryAction->setEnabled(false);
    m_nextHistoryAction->setEnabled(false);
    toolbarAction.insert(WebPage::Back,m_backHistoryAction);
    toolbarAction.insert(WebPage::Forward,m_nextHistoryAction);
    //toolbarAction.insert(WebPage::Reload,m_stopReloadAction);
    //toolbarAction.insert(WebPage::Stop,m_stopReloadAction);
}
void BrowserTab::configureURLField()
{
    m_urlField = new QLineEdit(defaultHomePage);
    m_urlIconAct = new QAction(m_urlField);
    m_urlField->setFocus(Qt::OtherFocusReason);
    m_urlField->setClearButtonEnabled(true);

    m_submit->setIcon(QIcon(":/fznavigator_icones/search_62.svg"));
    m_urlIconAct->setIcon(webView->favIcon());
    m_urlField->addAction(m_urlIconAct,QLineEdit::LeadingPosition);
    m_urlField->addAction(m_submit,QLineEdit::TrailingPosition);
}
void BrowserTab::insertActionInToTheToolbar()
{
    addActionsToTheToolbar(m_toolbar, m_backHistoryAction, m_nextHistoryAction,
                           m_stopReloadAction, m_homeAction,nullptr);
    QAction *sep = m_toolbar->insertSeparator(m_homeAction);
    separators.append(sep);
}
void BrowserTab::insertURLFIeldInToTheToolbar()
{
    m_toolbar->addWidget(m_urlField);
    //m_toolbar->addAction(m_submit);
}
void BrowserTab::linkToolbarActionsWithTheirIcons()
{
    m_backHistoryAction->setIcon(QIcon(":/fznavigator_icones/left_full.svg"));
    m_nextHistoryAction->setIcon(QIcon(":/fznavigator_icones/right_empty.svg"));
    m_stopReloadAction->setIcon(QIcon(":/fznavigator_icones/Reload.svg"));
    m_homeAction->setIcon(QIcon(":/fznavigator_icones/home_43.svg"));
}

void BrowserTab::configureConnectionsForToolbarActions()
{
    makeActionConnected(m_backHistoryAction,WebPage::Back);
    makeActionConnected(m_nextHistoryAction,WebPage::Forward);
    webViewConnections();
    actionsConnections();
}
void BrowserTab::setToolBarBehavior()
{
    m_toolbar->setMovable(false);
    m_toolbar->setFloatable(false);
    m_toolbar->toggleViewAction()->setVisible(false);
}
void BrowserTab::setUpCustomContexteMenu()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}
void BrowserTab::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("Context menu"), this);

   QAction action1("Remove Data Point", this);
   connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
   contextMenu.addAction(&action1);

   contextMenu.exec(mapToGlobal(pos));
}

/*Function called in the createNewWebPageView() function*/
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
/*Called in configureConnectionsForToolbarActions() function*/
void BrowserTab::makeActionConnected(QAction* act, WebPage::WebAction webAction)
{
    connect(act,&QAction::triggered,[this,webAction]{
             webView->triggerPageAction(webAction);});
}
void BrowserTab::webViewConnections()
{
    connect(webView,&WebPageView::webActionChanged,this,&BrowserTab::emitProgress);
    connect(webView,&WebPageView::shortcutActivated,
            webView,&WebPageView::triggerPageAction);
    connect(webView,&QWebEngineView::loadProgress,[this](int progress){
            emit loadProgress(progress);});
    connect(webView,&WebPageView::webActionChanged,this,
            &BrowserTab::handleWebActionChanged);
    connect(webView,&QWebEngineView::urlChanged,[this](const QUrl &url){
        m_urlField->setText(url.url());});

    connect(webView,&WebPageView::favIconChanged,
            webView,[this](const QIcon &icon){
            emit favIconSent(icon);
            m_urlIconAct->setIcon(icon);});
}
void BrowserTab::actionsConnections()
{
    QShortcut *reloadShortcut = new QShortcut(QKeySequence("CTRL+L"),this);
    connect(this,&BrowserTab::loadProgress,this,&BrowserTab::handleLoadProgress);
    connect(m_submit,&QAction::triggered,this,&BrowserTab::loadUrl);
    connect(m_urlField,&QLineEdit::returnPressed,this,&BrowserTab::loadUrl);
    connect(reloadShortcut,&QShortcut::activated,[this]{m_urlField->selectAll();
            m_urlField->setFocus(Qt::OtherFocusReason);});
    connect(m_homeAction,&QAction::triggered,this,&BrowserTab::goToHomePage);
}
void BrowserTab::emitProgress()
{
    emit loadProgress(webView->progress());
}
void BrowserTab::handleWebActionChanged(WebPage::WebAction webAct, bool state)
{
    if(webAct==WebPage::Reload || webAct==WebPage::Stop){return;}
    toolbarAction.value(webAct)->setEnabled(state);
}
void BrowserTab::handleLoadProgress(int progress)
{
    if(0<progress && progress<100){
        m_stopReloadAction->setData(WebPage::Stop);
        m_stopReloadAction->setToolTip(tr("Stop loading the current page"));
        m_stopReloadAction->setIcon(QIcon(":/fznavigator_icones/cancel.svg"));
        m_progress->setValue(progress);
    }else{
        m_stopReloadAction->setData(WebPage::Reload);
        m_stopReloadAction->setIcon(QIcon(":/fznavigator_icones/Reload.svg"));
        m_stopReloadAction->setToolTip(tr("Reload the current page"));
        m_progress->setValue(0);
    }
    m_urlIconAct->setIcon(webView->favIcon());
    int stopReloadWebAct = m_stopReloadAction->data().toInt();
    makeActionConnected(m_stopReloadAction,WebPage::WebAction(stopReloadWebAct));
}
void BrowserTab::loadUrl()
{
    QString url = this->m_urlField->text();
    url = preconfigureUrl(url);
    webView->load(QUrl(url));
}
void BrowserTab::goToHomePage()
{
   webView->load(QUrl(defaultHomePage));
}


/*Public getters*/
WebPageView* BrowserTab::view()
{
    return webView;
}
WebPage *BrowserTab::page()
{
    return webPage;
}
/*Public setters*/
