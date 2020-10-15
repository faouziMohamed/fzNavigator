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
    insertWebPageView(url);
    addToolbar();
    addStatusBar();
    addCustomContexteMenu();
}


void BrowserTab::closeEvent(QCloseEvent *event){
    event->accept();
}

/*Functions called in the Constructor */
void BrowserTab::insertWebPageView(QString url)
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
    addActions();
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
    m_toolbar =  this->addToolBar(tr("Navigation"));
    m_back = new QAction(tr("Previous page"));
    m_next = new QAction(tr("Next Page"));
    m_stop_relod  = new QAction(this);
    m_home        = new QAction(tr("Home"));
    m_submit            = new QAction(tr("Go"));

    m_back->setEnabled(false);
    m_next->setEnabled(false);
    toolbarAction.insert(WebPage::Back,m_back);
    toolbarAction.insert(WebPage::Forward, m_next);
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
void BrowserTab::addActions()
{
    initializeActions();
    linkActWithIcons();
    Fz::addActionsToTheToolbar(
         m_toolbar, m_back, m_next, m_stop_relod, m_home, nullptr);
    m_toolbar->insertSeparator(m_home);
}
void BrowserTab::addURLField()
{
    configureURLField();
    m_toolbar->addWidget(m_urlField);
}

void BrowserTab::addOptionsMenu(){
    configOptionMenu();
    m_toolbar->addWidget(m_toolButton);
}
void BrowserTab::configOptionMenu()
{
    m_optionMenu = new QMenu("&Options");
    m_toolButton = new QToolButton(m_toolbar);
    m_toolButton->setMenu(m_optionMenu);
    m_toolButton->setPopupMode(QToolButton::InstantPopup);
    m_toolButton->setIcon(Fz::menuOptIcon());
    m_toolButton->setLayoutDirection(Qt::LeftToRight);

    QAction *dev = m_optionMenu->addAction(tr("Open &Developer Tool"));
    QAction *setting = m_optionMenu->addAction(tr("&Preferences"));
    m_optionMenu->addSeparator();
    QAction *quit = m_optionMenu->addAction(tr("&Quit"));    
}
void BrowserTab::linkActWithIcons()
{
    m_back->setIcon(Fz::backIcon());
    m_next->setIcon(Fz::forwardIcon());
    m_stop_relod->setIcon(Fz::stopLoadIcon());
    m_home->setIcon(Fz::homeIcon());
}

void BrowserTab::setUpActConnection()
{
    makeActionConnected(m_back, WebPage::Back);
    makeActionConnected(m_next, WebPage::Forward);
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
    connect(m_home,&QAction::triggered,this,&BrowserTab::goToHomePage);
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
        m_stop_relod->setData(WebPage::Stop);
        m_stop_relod->setToolTip(tr("Stop loading the current page"));
        m_stop_relod->setIcon(Fz::stopLoadIcon());
        m_progress->setValue(progress);
    }else{
        m_stop_relod->setData(WebPage::Reload);
        m_stop_relod->setIcon(Fz::reloadIcon());
        m_stop_relod->setToolTip(tr("Reload the current page"));
        m_progress->setValue(0);
    }
    m_url_field_favIconAct->setIcon(webView->favIcon());
    int stopReloadWebAct = m_stop_relod->data().toInt();
    makeActionConnected(m_stop_relod,WebPage::WebAction(stopReloadWebAct));
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
