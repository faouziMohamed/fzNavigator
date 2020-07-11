#include "webEngineTools.h"

WebEngineTools::WebEngineTools(QWidget* parent, QString url)
    :QMainWindow(parent)
{
    addToolbar();
    addStatusBar();
    addShortcut();

    if(url.isEmpty ()){
        url = "http://www.duckduckgo.com/";
    }
    newPage(url);
    this->resize(1024,650);
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

WebEngineTools *WebEngineTools::newPage(QString url)
{
     QWidget *tab = new QWidget(this);
     m_webPage = new QWebEngineView;

     QVBoxLayout *layout = new QVBoxLayout(tab);
       layout->setContentsMargins(0,0,0,0);
       layout->addWidget(m_webPage);
     tab->setLayout(layout);
    this->setCentralWidget(tab);

    bool space = false, dot = false;
    /*Verify if a url was typed or a keyword to search in the adress bar*/
    for(int i=0;i<url.size();i++)
    {
         if(url[i]==' ')
         {
             url[i]='+';
             space = true;
         }
         else if(url[i]=='.')
             dot = true;
     }

    if(url.isEmpty())
    {
        url = "https:// ";
    }
    else
    {
        if( (url.left(7) != "http://") && (url.left(8) != "https://" ) )
        {
            if(space || (!dot)) //Submitting the research
               url = "http://duckduckgo.com/?q="+url+"&t=h_&ia=web";
            else
               url = "http://"+url;
        }
    }
    m_webPage->load(QUrl(url));

    connect(m_webPage,SIGNAL(urlChanged(QUrl)),this,SLOT(changeUrl(QUrl)));
    connect(m_webPage,SIGNAL(titleChanged(QString)),this,SLOT(changeTitle(QString)));
    connect(m_webPage,SIGNAL(loadStarted()),this,SLOT(initLoading()));
    connect(m_webPage,SIGNAL(loadProgress(int)),this,SLOT(loading(int)));
    connect(m_webPage,SIGNAL(loadFinished(bool)),this,SLOT(endOfLoad(bool)));
    connect(m_webPage,SIGNAL(iconChanged(const QIcon&)),this,SLOT(changeIcon(const QIcon&)));
    return this;
}
void WebEngineTools::changeUrl(QUrl url)
{
    m_urlField->setText(url.toString());
}
void WebEngineTools::changeTitle(QString title)
{
    this->m_title = title;
    this->setWindowTitle(title);
}
void WebEngineTools::initLoading()
{
    m_progress->reset();
    m_progress->setVisible(true);
}
void WebEngineTools::loading(int value)
{
    m_progress->setValue(value);
    m_refreshAction->setVisible(false);
    m_stopAction->setVisible(true);
}
void WebEngineTools::endOfLoad(bool visible)
{
    if(visible)
    {
        m_progress->setVisible(false);
        this->statusBar()->showMessage(tr("Ready"),3000);
        m_refreshAction->setVisible(true);
        m_stopAction->setVisible(false);
    }
}
void WebEngineTools::changeIcon(const QIcon &icon)
{
    this->m_icon = icon;
    this->setWindowIcon(m_icon);
}

void WebEngineTools::addToolbar()
{
    m_toolbar = new QToolBar;
      m_previousPageAction = new QAction(tr("Previous page"));
      m_nextPageAction     = new QAction(tr("Next Page"));
      m_refreshAction      = new QAction(tr("Refresh"));
      m_stopAction         = new QAction(tr("Stop"));
      m_homeAction         = new QAction(tr("Home"));

    m_toolbar = this->addToolBar(tr("Navigation"));
    m_toolbar->addAction(m_previousPageAction);
    m_toolbar->addAction(m_nextPageAction);
    m_toolbar->addAction(m_refreshAction);
    m_toolbar->addAction(m_stopAction);
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_homeAction);

    m_urlField = new QLineEdit(defaultHomePage);
    m_urlField->setFocus(Qt::OtherFocusReason);
    m_urlField->selectAll();
    m_toolbar->addWidget(m_urlField);
    m_submit = new QAction(tr("Go"));
    m_toolbar->addAction(m_submit);

    m_previousPageAction->setIcon(QIcon(":/fznavigator_icones/prev.png"));
        m_nextPageAction->setIcon(QIcon(":/fznavigator_icones/next.png"));
         m_refreshAction->setIcon(QIcon(":/fznavigator_icones/refresh.png"));
            m_homeAction->setIcon(QIcon(":/fznavigator_icones/home.png"));
            m_stopAction->setIcon(QIcon(":/fznavigator_icones/stop.png"));
                m_submit->setIcon(QIcon(":/fznavigator_icones/go.png"));
}
void WebEngineTools::loadUrl()
{
    QString url = this->m_urlField->text();
    bool space = false, dot = false;
    /*Verify if a url was typed or a keyword to search in the adress bar*/
    for(int i=0;i<url.size();i++)
    {
         if(url[i]==' ')
         {
             url[i]='+';
             space = true;
         }
         else if(url[i]=='.')
             dot = true;
     }

    if(url.isEmpty())
    {
        url = "https:// ";
    }
    else
    {
        if( (url.left(7) != "http://") && (url.left(8) != "https://" ) )
        {
            if(space || (!dot)) //Submitting the research
               url = "http://duckduckgo.com/?q="+url+"&t=h_&ia=web";
            else
               url = "http://"+url;
        }
    }
    this->m_webPage->load(QUrl(url));
    this->m_icon = QIcon();
}

void WebEngineTools::addStatusBar()
{
    m_progress = new QProgressBar;
    m_progress->reset();
    m_progress->setVisible(false);
    this->statusBar()->addWidget(m_progress,1);
}
void WebEngineTools::addShortcut()
{
    this->m_previousPageAction->setShortcut(QKeySequence(QKeySequence::Back));
        this->m_nextPageAction->setShortcut(QKeySequence(QKeySequence::Forward));
         this->m_refreshAction->setShortcut(QKeySequence(QKeySequence::Refresh));
            this->m_stopAction->setShortcut(QKeySequence(QKeySequence::Cancel));

   connect(new QShortcut(QKeySequence("CTRL+R"),this),SIGNAL(activated()),this,SLOT(refresh()));
   connect(m_previousPageAction,SIGNAL(triggered())    ,this,SLOT(previous()));
   connect(m_nextPageAction    ,SIGNAL(triggered())    ,this,SLOT(next()));
   connect(m_refreshAction     ,SIGNAL(triggered())    ,this,SLOT(refresh()));
   connect(m_stopAction        ,SIGNAL(triggered())    ,this,SLOT(stop()));
   connect(m_homeAction        ,SIGNAL(triggered())    ,this,SLOT(goHome()));
   connect(m_submit            ,SIGNAL(triggered())    ,this,SLOT(loadUrl()));
   connect(m_urlField          ,SIGNAL(returnPressed()),this,SLOT(loadUrl()));
}
//Toolbar & Menu Action's Slot
void WebEngineTools::previous()
{
    this->m_webPage->back();
}
void WebEngineTools::next()
{
    this->m_webPage->forward();
}
void WebEngineTools::refresh()
{
    this->m_webPage->reload();
}
void WebEngineTools::goHome()
{
   this->m_webPage->load(QUrl(defaultHomePage));
}
void WebEngineTools::stop()
{
   this->m_webPage->stop();
}
QWebEngineView* WebEngineTools::getWebEngine(){
    return this->centralWidget()->findChild<QWebEngineView*>();
}
