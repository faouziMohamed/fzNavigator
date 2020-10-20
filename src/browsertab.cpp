#include "header/browsertab.h"
#include "header/tabwidget.h"

BrowserTab::BrowserTab(QWidget *parent
                       , QWebEngineProfile *profile
                       , WebPageView *view
                       , QString url)
    : QMainWindow(parent)
    , m_Profile(profile)
    , webView(view)
{
    addWebPageView(url);
    addToolbar();
    addStatusBar();
    addCustomContexteMenu();
}


void BrowserTab::closeEvent(QCloseEvent *event){
    event->accept();
}

/*Functions called in the Constructor */
void BrowserTab::addWebPageView(QString url)
{
    if(webView!=nullptr){
        url = webView->url().toString();
    }
    else if(url.isEmpty()){
        url = m_defaultHomePage;
    }
    createNewWebPageView(url);
}
void BrowserTab::addToolbar()
{
    addBtnActions();
    addURLField();
    addOptionsMenu();
    setUpActConnection();
    configureToolBar();
}
void BrowserTab::addStatusBar()
{
    m_progress = new QProgressBar;
    m_progress->reset();
    m_progress->setVisible(false);
    statusBar()->addWidget(m_progress,1);
    statusBar()->setVisible(false);
}
void BrowserTab::addCustomContexteMenu()
{
    configContextMenu();
}

BrowserTab *BrowserTab::createNewWebPageView(QString url)
{
    createWebPageLayout();
    url = preconfigureUrl(url);
    webView->load(QUrl(url));
    return this;
}
/*Function called in the function addToolbar*/
void BrowserTab::initializeActions()
{
    
}
void BrowserTab::configureURLField()
{
    m_urlField = new QLineEdit(m_defaultHomePage);
    m_url_field_favIconAct = new QAction(m_urlField);
    m_urlField->setFocus(Qt::OtherFocusReason);
    m_urlField->setClearButtonEnabled(true);

    m_submit->setIcon(Fz::submitIcon());
    m_url_field_favIconAct->setIcon(webView->favIcon());
    m_urlField->addAction(m_url_field_favIconAct, QLineEdit::LeadingPosition);
    m_urlField->addAction(m_submit, QLineEdit::TrailingPosition);
}
void BrowserTab::addBtnActions()
{
    //initializeActions();
    
    m_toolbar =  this->addToolBar(tr("Navigation"));

    m_btnBack = new QPushButton(Fz::backIcon(), "");
    m_btnNext = new QPushButton(Fz::forwardIcon(),"");
    m_stop_relod  = new QPushButton(Fz::stopLoadIcon(),"");
    m_home        = new QPushButton(Fz::homeIcon(),"");
    m_submit      = new QAction(tr("Go"));
    
    m_actBack = m_toolbar->addWidget(m_btnBack);
    m_actNext = m_toolbar->addWidget(m_btnNext);
    m_toolbar->addSeparator();
    m_actStopReload = m_toolbar->addWidget(m_stop_relod);
    m_toolbar->addWidget(m_home);
    
    m_actBack->setEnabled(false);
    m_actNext->setEnabled(false);
    toolbarAction.insert(WebPage::Back, m_actBack);
    toolbarAction.insert(WebPage::Forward, m_actNext);

    /*Fz::addActionsToTheToolbar(
         m_toolbar, m_back, m_next, m_stop_relod, m_home, nullptr);*/
}
void BrowserTab::addURLField()
{
    configureURLField();
    m_toolbar->addWidget(m_urlField);
}

void BrowserTab::addOptionsMenu(){
    configOptionMenu();
    addOptions();
    m_toolbar->addWidget(m_toolButton);
}
void BrowserTab::addOptions()
{
    QAction *newTab    = m_optionMenu->addAction(tr("New &Tab"));
    QAction *newWindow = m_optionMenu->addAction(tr("New &Window"));
    QAction *pWindow   = m_optionMenu->addAction(tr("New &private Window"));
    m_optionMenu->addSeparator();
    
    /*QAction *newTab    = */m_optionMenu->addAction(tr("&History"));
    /*QAction *newTab    = */m_optionMenu->addAction(tr("&Bookmarks"));
    /*QAction *newTab    = */m_optionMenu->addAction(tr("&Downloads"));
    m_optionMenu->addSeparator();
    
    /*QAction *settings = */m_optionMenu->addAction(tr("&Settings"));
    /*QAction *about = */m_optionMenu->addAction(tr("&About %1").arg(FZ_NAV_NAME));
    m_optionMenu->addSeparator();
    QAction *quit = m_optionMenu->addAction(tr("&Exit"));
    
    connect(quit, &QAction::triggered, this, [this](){
        emit exitRequested(); });
}

void BrowserTab::configOptionMenu()
{
    m_optionMenu = new QMenu("&Options");
    m_toolButton = new QToolButton(m_toolbar);
    m_toolButton->setMenu(m_optionMenu);
    m_toolButton->setPopupMode(QToolButton::InstantPopup);
    m_toolButton->setIcon(Fz::menuOptIcon());
    m_toolButton->setLayoutDirection(Qt::LeftToRight);
}

void BrowserTab::setUpActConnection()
{
    makeActionConnected(m_btnBack, WebPage::Back);
    makeActionConnected(m_btnNext, WebPage::Forward);
    webViewConnections();
    actionsConnections();
}
void BrowserTab::configureToolBar()
{
    m_toolbar->setMovable(false);
    m_toolbar->setFloatable(false);
    m_toolbar->toggleViewAction()->setVisible(false);
}
void BrowserTab::configContextMenu()
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
    configureWebPageView();
    handleReceivedSignals();
    return addWebViewToLayout();
}

void BrowserTab::configureWebPageView()
{
    if(webView == nullptr) {
        webView = new WebPageView(nullptr, m_Profile);
    }
    webPage = new WebPage(webView, m_Profile);
    webView->setPage(webPage);
    webView->setHomePage(defaultHomePage());
}

void BrowserTab::handleReceivedSignals()
{
  connect(webView, &WebPageView::newFgTabRequested, [this](BrowserTab* tab){
      emit this->newFgTabRequired(tab);
  });

  connect(webView, &WebPageView::newBgTabRequested, [this](BrowserTab* tab){
      emit this->newBgTabRequired(tab);
  });

  connect(webView, &WebPageView::newWindowRequested, [this](BrowserTab* tab){
      emit newWindowTabRequired(tab);
  });

  connect(webView, &WebPageView::newDialogRequested, [this](WebPageView* view){
      emit this->newDialogTabRequired(view);
  });
  
  //QFrame *frambox = new QFrame(this);
  //connect(webView->page(), &WebPage::ho)
  
}

QWidget* BrowserTab::addWebViewToLayout()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(webView);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setDocumentMode(true);
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


/*Called in setUpActConnection() function*/
void BrowserTab::makeActionConnected(QPushButton* btn, WebPage::WebAction webAction)
{
    connect(btn,&QPushButton::clicked,[this,webAction](){
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

    connect(webView,&WebPageView::favIconChanged,[this](const QIcon &icon){
            emit favIconSent(icon);
            m_url_field_favIconAct->setIcon(icon);});
            
    connect(webView, &WebPageView::linkTextRequested, [](const QString& text){
        QClipboard *clipBoard = QApplication::clipboard();
        clipBoard->setText(text);
    });
}
void BrowserTab::actionsConnections()
{
    QShortcut *selectUrlField;
    selectUrlField = new QShortcut(QKeySequence("CTRL+L"),this);
    connect(this,&BrowserTab::loadProgress,this,&BrowserTab::handleLoadProgress);
    connect(m_submit,&QAction::triggered,this,&BrowserTab::loadUrl);
    connect(m_urlField,&QLineEdit::returnPressed,this,&BrowserTab::loadUrl);
    connect(selectUrlField,&QShortcut::activated,[this]{m_urlField->selectAll();
            m_urlField->setFocus(Qt::OtherFocusReason);});
    connect(m_home,&QPushButton::clicked,this,&BrowserTab::goToHomePage);
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
        m_actStopReload->setData(WebPage::Stop);
        m_stop_relod->setToolTip(tr("Stop loading the current page"));
        m_stop_relod->setIcon(Fz::stopLoadIcon());
        m_progress->setValue(progress);
    }else{
        m_actStopReload->setData(WebPage::Reload);
        m_stop_relod->setIcon(Fz::reloadIcon());
        m_stop_relod->setToolTip(tr("Reload the current page"));
        m_progress->setValue(0);
    }
    m_url_field_favIconAct->setIcon(webView->favIcon());
    int stopReloadWebAct = m_actStopReload->data().toInt();
    makeActionConnected(m_stop_relod, WebPage::WebAction(stopReloadWebAct));
}
void BrowserTab::loadUrl()
{
    QString url = this->m_urlField->text();
    url = preconfigureUrl(url);
    webView->load(QUrl(url));
}
void BrowserTab::goToHomePage()
{
   webView->load(QUrl(m_defaultHomePage));
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

void BrowserTab::setView(WebPageView *view)
{
    this->webView = view;
}

const QString &BrowserTab::defaultHomePage()
{
    return m_defaultHomePage;
}
/*Public setters*/
