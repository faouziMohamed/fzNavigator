#include "header/tabwidget.h"

TabWidget::TabWidget(QWebEngineProfile *profile
                     , TabsBehavior::Tabs how
                     , QWidget * parent)
    : QTabWidget(parent)
    , fznavName(tr("Fz Navigator"))
    , newTabTitle(tr("New Tab - Fz Navigator"))
    , m_profile(profile)
{
    if(how == TabsBehavior::NewTab){
        //addNewTab();
        addFirstTab(TabWidget::ForegroundTab);
    }
    setupTabsBehavior();
    setUpMainConnexions();
    setAttribute(Qt::WA_DeleteOnClose, true);
}
void TabWidget::setupTabsBehavior()
{
    setMovable(true);
    setTabsClosable(true);
    setFocus(Qt::MouseFocusReason);
}

void TabWidget::setUpMainConnexions()
{
    //QShortcut *newTab = new QShortcut(QKeySequence::AddTab,this);
    QShortcut *newTab;
    QShortcut *newWindow;
    
    newTab = new QShortcut(QKeySequence(Qt::CTRL|Qt::Key_T), this);
    newWindow = new QShortcut(QKeySequence(Qt::CTRL|Qt::Key_N), this);
    connect(newTab, SIGNAL(activated()), this, SLOT(addNewTab()));
    connect(newWindow,&QShortcut::activated, [this](){
        //WebPageView *pageView = new WebPageView(nullptr, m_profile); 
        //BrowserTab* tab;
        //addNewTab(pageView, TabWidget::BrowserWindow);
        //TODO : select a profile that the use ask!!
        BrowserTab *aNewTab = new BrowserTab(nullptr, nullptr);
        TabWidget *tab = newBrowserWindow(aNewTab);
        emit windowRequired(tab);
        });

    connect(this, &QTabWidget::currentChanged,[this](int index){
        if(index!=-1){
            QString winTitle = tabText(index) + " - " + fznavName;
            emit customWindowTitleChanged(winTitle);
        }
    });

    connect(this,&TabWidget::tabCloseRequested,[this](int index){
        BrowserTab *tab = tabAt(index);
        removeTab(index);
        //TODO:deleteLater() the removed widget and backup it url 
        //if user need to reopen later
        if(count()>0)
        {currentTab()->setFocus();}
        else 
        {
            this->close();
            Browser *parent = qobject_cast<Browser*>(this->parent()); 
            if(parent != nullptr){
                parent->close();
            }
        }
        tab->deleteLater();
    });
}

void TabWidget::closeEvent(QCloseEvent *event)
{
    if (count() > 1) 
    {
        int ret = QMessageBox::warning(this, tr("Confirm close"),
                                       tr("Are you sure you want to close the window ?\n"
                                          "There are %1 tabs open.").arg(count()),
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret == QMessageBox::No) {
            event->ignore();
            return;
        }
    }
    //event->accept();
    //deleteLater();
}

QWidget* TabWidget::addFirstTab(TabWidget::Window type)
{
   WebPageView * view = new WebPageView(nullptr, m_profile);
   view->setUrl(QUrl(view->homePage()));
   return addNewTab(view, type);
}

QWidget* TabWidget::addNewTab(WebPageView *webView, TabWidget::Window type)
{
   BrowserTab *newTab = new BrowserTab(this, m_profile, webView);
   return addNewTab(newTab, type);
}

QWidget* TabWidget::addNewTab(BrowserTab *newTab, TabWidget::Window type)
{
   switch (type) {
     case TabWidget::ForegroundTab: return newForeground(newTab);
     case TabWidget::BackgroundTab: return newBackgroundTab(newTab);
     case TabWidget::BrowserWindow: {return newBrowserWindow(newTab);}
     case TabWidget::DialogWindow : {
                                          WebPageView* view = newTab->view();
                                          view->setParent(nullptr);
                                          newTab->deleteLater();
                                          return newDialogWindow(view);
                                        }   
     default: break; //Added only to suppress Warning : Enumeration value 
                     //                             not handled in switch
   }
   return nullptr;
}

BrowserTab *TabWidget::newForeground(BrowserTab *newTab)
{
    newBackgroundTab(newTab);
    setCurrentWidget(newTab);
    return newTab;
}

BrowserTab *TabWidget::newBackgroundTab(BrowserTab *newTab)
{
    int index = addTab(newTab, newTabTitle);
    WebPageView* view = newTab->view();
    setTabIcon(index, view->favIcon());
    return configureNewTab(newTab);
}

TabWidget *TabWidget::newBrowserWindow(BrowserTab *aNewTab)
{
    TabWidget *newWindow;
    QWebEngineProfile *profil = QWebEngineProfile::defaultProfile();
    newWindow = new TabWidget(profil, TabsBehavior::NoNewTab, nullptr);
    newWindow->addNewTab(aNewTab, TabWidget::ForegroundTab);
    //newWindow->show();
    return nullptr;
}

WebPageView *TabWidget::newDialogWindow(WebPageView *pageView)
{
    // TODO: Replace with a BrowserTab but url tab not editable and no toolbar
    pageView->show();
    return pageView;
}


BrowserTab* TabWidget::configureNewTab(BrowserTab* newTab)
{
    setUpTabConnexions(newTab);
    setUserTheme("://style/userTheme.css");
    return newTab;  
}


void TabWidget::setUpTabConnexions(BrowserTab* newTab)
{
    WebPageView *view = newTab->view();
    //int index = indexOf(newTab);
    connect(newTab,&BrowserTab::favIconSent,
        [this,newTab](const QIcon& icon){setTabIcon(indexOf(newTab),icon);});
   
    connect(view,&WebPageView::titleChanged,
        [this,newTab](const QString &title)
        {
            setTabText(indexOf(newTab),title.left(25));
            setTabToolTip(indexOf(newTab),title);
        });
          
    connect(view,&WebPageView::titleChanged,
        [this, newTab](const QString &title)
        {
            if(currentIndex()==indexOf(newTab)){
                QString winTitle = title + " - " + fznavName;
                emit customWindowTitleChanged(winTitle);
            }
        });
    
    connect(newTab, &BrowserTab::newFgTabRequired, [this](BrowserTab* tab){
        this->addNewTab(tab, TabWidget::ForegroundTab);
    });
    
    connect(newTab, &BrowserTab::newBgTabRequired, [this](BrowserTab* tab){
        this->addNewTab(tab, TabWidget::BackgroundTab);
    });
    
    connect(newTab, &BrowserTab::newWindowTabRequired,
        [this](BrowserTab* tab){
            TabWidget* aWindow = newBrowserWindow(tab);
            emit windowRequired(aWindow);
        });

    connect(newTab, &BrowserTab::newDialogTabRequired, 
        [this](WebPageView* pageView)
        {
            this->addNewTab(pageView, TabWidget::DialogWindow);
        });
}

BrowserTab* TabWidget::currentTab()
{
    return  qobject_cast<BrowserTab*>(currentWidget());
}

BrowserTab* TabWidget::tabAt(int index)
{
    return  qobject_cast<BrowserTab*>(QTabWidget::widget(index));
}

QString TabWidget::setUserTheme(const QString &cssFile)
{
    QFile styleFile(cssFile);
    styleFile.open(QFile::ReadOnly);
    QString qssStyle = QLatin1String(styleFile.readAll());
    setStyleSheet(qssStyle);
    return styleSheet();
}


/*
void TabWidget::handleContextMenuRequested()
{
    QMenu menu;
    QAction *action = menu.addAction(tr("Clone Tab"));
    menu.addSeparator();
    action = menu.addAction(tr("&Close Tab"));
    action->setShortcut(QKeySequence::Close);
    action = menu.addAction(tr("Close &Other Tabs"));
    menu.addSeparator();
    action = menu.addAction(tr("Reload Tab"));
    menu.exec(QCursor::pos());
}*/
