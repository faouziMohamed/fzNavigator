#include "header/webEngineTools.h"

WebEngineTools::WebEngineTools(QWidget* parent, QString url)
    :QMainWindow(parent)
{
    addToolbar();
    addStatusBar();
    configureToolbarActionsShortcuts();
    configureToolbarActionsConnections();
    configureOppeningWindowSize();
    initialURLLoad(url);
}
void WebEngineTools::addToolbar()
{
    initialiseMainToolbarAction();
    configureURLField();
    insertActionInToTheToolbar();
    insertURLFIeldInToTheToolbar();
    linkToolbarActionsWithTheirIcons();
}
void WebEngineTools::addStatusBar()
{
    m_progress = new QProgressBar;
    m_progress->reset();
    m_progress->setVisible(false);
    this->statusBar()->addWidget(m_progress,1);
}
void WebEngineTools::configureToolbarActionsShortcuts()
{
    this->m_previousPageAction->setShortcut(QKeySequence(QKeySequence::Back));
    this->m_nextPageAction->setShortcut(QKeySequence(QKeySequence::Forward));
    this->m_refreshAction->setShortcut(QKeySequence(QKeySequence::Refresh));
    this->m_stopAction->setShortcut(QKeySequence(QKeySequence::Cancel));
}
void WebEngineTools::configureToolbarActionsConnections()
{
    connect(new QShortcut(QKeySequence("CTRL+R"),this),
            SIGNAL(activated()),this,SLOT(refreshPage()));
    connect(m_previousPageAction,SIGNAL(triggered())    ,this,SLOT(previousPage()));
    connect(m_nextPageAction    ,SIGNAL(triggered())    ,this,SLOT(nextPage()));
    connect(m_refreshAction     ,SIGNAL(triggered())    ,this,SLOT(refreshPage()));
    connect(m_stopAction        ,SIGNAL(triggered())    ,this,SLOT(stopPageLoading()));
    connect(m_homeAction        ,SIGNAL(triggered())    ,this,SLOT(goToHomePage()));
    connect(m_submit            ,SIGNAL(triggered())    ,this,SLOT(loadUrl()));
    connect(m_urlField          ,SIGNAL(returnPressed()),this,SLOT(loadUrl()));
}
void WebEngineTools::configureOppeningWindowSize()
{
    this->resize(1024,650);
}
void WebEngineTools::initialURLLoad(QString url)
{
    if(url.isEmpty ()){
        url = "http://www.duckduckgo.com/";
    }
    newPage(url);
}

void WebEngineTools::initialiseMainToolbarAction()
{
    m_toolbar =  this->addToolBar(tr("Navigation"));
    m_previousPageAction = new QAction(tr("Previous page"));
    m_nextPageAction     = new QAction(tr("Next Page"));
    m_refreshAction      = new QAction(tr("Refresh"));
    m_stopAction         = new QAction(tr("Stop"));
    m_homeAction         = new QAction(tr("Home"));
    m_submit             = new QAction(tr("Go"));
}
void WebEngineTools::configureURLField()
{
    m_urlField = new QLineEdit(defaultHomePage);
    m_urlField->setFocus(Qt::OtherFocusReason);
}
void WebEngineTools::insertActionInToTheToolbar()
{
    addActionsToTheToolbar(m_toolbar, m_previousPageAction, m_nextPageAction,
                           m_refreshAction, m_stopAction, m_homeAction,nullptr);
    m_toolbar->insertSeparator(m_homeAction);
}
void WebEngineTools::insertURLFIeldInToTheToolbar()
{
    m_toolbar->addWidget(m_urlField);
    m_toolbar->addAction(m_submit);
}
void WebEngineTools::linkToolbarActionsWithTheirIcons()
{
    m_previousPageAction->setIcon(QIcon(":/fznavigator_icones/prev.png"));
        m_nextPageAction->setIcon(QIcon(":/fznavigator_icones/next.png"));
         m_refreshAction->setIcon(QIcon(":/fznavigator_icones/refresh.png"));
            m_homeAction->setIcon(QIcon(":/fznavigator_icones/home.png"));
            m_stopAction->setIcon(QIcon(":/fznavigator_icones/stop.png"));
                m_submit->setIcon(QIcon(":/fznavigator_icones/go.png"));
}
WebEngineTools *WebEngineTools::newPage(QString url)
{
    createWebPageLayout();
    /*Verify if a url was typed or a keyword to search in the adress bar*/
    url = preconfigureUrl(url);
    m_webPage->load(QUrl(url));
    configureEngineConnection();
    return this;
}

void WebEngineTools::addActionsToTheToolbar(QToolBar* aToolbar,...)
{
    va_list listOfvariableArguments;
    va_start(listOfvariableArguments, aToolbar);
    QAction *currentAction = va_arg(listOfvariableArguments, QAction *);
    while(currentActionIsNotNull(currentAction))
    {
        aToolbar->addAction(currentAction);
        currentAction = va_arg(listOfvariableArguments, QAction *);
    }
    va_end(listOfvariableArguments);
}
QWidget* WebEngineTools::createWebPageLayout()
{
    QWidget *centralViewWidget = new QWidget(this);
    m_webPage = new QWebEngineView;
    QVBoxLayout *layout = new QVBoxLayout(centralViewWidget);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_webPage);
    centralViewWidget->setLayout(layout);
    this->setCentralWidget(centralViewWidget);
    return centralViewWidget;
}
QString WebEngineTools::preconfigureUrl(QString url)
{
    url = url.replace('%',"%25");
    if(url.isEmpty())
    {
        url = "https:// ";
        return url;
    }

    if( (url.left(7) != "http://") && (url.left(8) != "https://" ) )
    {
        if(isNotAnUrlSyntaxe(url))
           url = "http://duckduckgo.com/?q="+url.replace(' ','+');
        else
           url = "http://"+url;
    }
    return url;
}
void WebEngineTools::configureEngineConnection()
{
    connect(m_webPage,SIGNAL(urlChanged(QUrl)),this,SLOT(changeUrl(QUrl)));
    connect(m_webPage,SIGNAL(titleChanged(QString)),this,
            SLOT(changeThisWindowTitle(QString)));
    connect(m_webPage,SIGNAL(loadStarted()),this,
            SLOT(atTheStartOfPageLoading()));
    connect(m_webPage,SIGNAL(loadProgress(int)),this,
            SLOT(whilePageIsLoading(int)));
    connect(m_webPage,SIGNAL(loadFinished(bool)),this,
            SLOT(atTheEndOfPageLoading(bool)));
    connect(m_webPage,SIGNAL(iconChanged(const QIcon&)),this,
            SLOT(changeWindowFavcon(const QIcon&)));
}

bool currentActionIsNotNull(QAction *action){
    return action != nullptr;
}
bool isNotAnUrlSyntaxe(QString url)
{
    QChar dot = '.', space = ' ';
    return  url.contains(space)||
            (!url.contains(dot));
}

void WebEngineTools::changeUrl(QUrl url)
{
    m_urlField->setText(url.toString());
}
void WebEngineTools::changeThisWindowTitle(QString title)
{
    this->m_title = title;
    this->setWindowTitle(title);
}
void WebEngineTools::atTheStartOfPageLoading()
{
    m_progress->reset();
    m_progress->setVisible(true);
}
void WebEngineTools::whilePageIsLoading(int value)
{
    m_progress->setValue(value);
    m_refreshAction->setVisible(false);
    m_stopAction->setVisible(true);
}
void WebEngineTools::atTheEndOfPageLoading(bool visible)
{
    if(visible)
    {
        m_progress->setVisible(false);
        this->statusBar()->showMessage(tr("Ready"),3000);
        m_refreshAction->setVisible(true);
        m_stopAction->setVisible(false);
    }
}
void WebEngineTools::changeWindowFavcon(const QIcon &icon)
{
    this->m_icon = icon;
    this->setWindowIcon(m_icon);
}
void WebEngineTools::loadUrl()
{
    QString url = this->m_urlField->text();
    url = preconfigureUrl(url);
    this->m_webPage->load(QUrl(url));
    this->m_icon = QIcon();
}
void WebEngineTools::previousPage()
{
    this->m_webPage->back();
}
void WebEngineTools::nextPage()
{
    this->m_webPage->forward();
}
void WebEngineTools::refreshPage()
{
    this->m_webPage->reload();
}
void WebEngineTools::goToHomePage()
{
   this->m_webPage->load(QUrl(defaultHomePage));
}
void WebEngineTools::stopPageLoading()
{
   this->m_webPage->stop();
}
QWebEngineView* WebEngineTools::getWebEngine(){
    return this->centralWidget()->findChild<QWebEngineView*>();
}

WebEngineTools::~WebEngineTools()
{
    delete m_webPage;
    delete m_toolbar;
    delete m_homeAction;
    delete m_submit;
    delete m_urlField;
    delete m_previousPageAction;
    delete m_nextPageAction;
    delete m_refreshAction;
    delete m_stopAction;
    delete m_progress;
}
