#include "header/tabwidget.h"

TabWidget::TabWidget(QWebEngineProfile *profile, QWidget * parent)
    : QTabWidget(parent)
    , fznavName("Fz Navigator")
    , newTabTitle("About:Blank - Fz Navigo")
    , m_profile(profile)
{
    tab = addNewTab();
    setupTabsBehavior();
    QShortcut *newtabShortcut = new QShortcut(QKeySequence::AddTab,this);
    connect(newtabShortcut,SIGNAL(activated()),this,SLOT(addNewTab()));
    connect(this,&QTabWidget::currentChanged,[this](int index){
        if(index!=-1){
            QString winTitle = tabText(index) + " - " + fznavName;
            emit customWindowTitleChanged(winTitle);
        }
    });

    connect(this,&TabWidget::customWindowTitleChanged,
            [this](const QString &title){
            setWindowTitle(title);
    });



    this->setWindowIcon(QIcon(":/fznavigator_icones/web.png"));
}

BrowserTab* TabWidget::addNewTab()
{
   BrowserTab *newTab = new BrowserTab(this,m_profile);
   WebPageView* view = newTab->view();
   int index = addTab(newTab,newTabTitle);
   setCurrentIndex(index);
   setTabIcon(index,view->favIcon());

   setUpTabConnexions(newTab,index);
   themeDarkAurore(newTab);
   return newTab;
}

void TabWidget::setUpTabConnexions(BrowserTab* newTab,int tabIndex)
{
    WebPageView *view = newTab->view();

    connect(newTab,&BrowserTab::favIconSent,[this,tabIndex](const QIcon& icon){
        setTabIcon(tabIndex,icon);});
    connect(view,&WebPageView::titleChanged,[this,tabIndex](const QString &title){
        setTabText(tabIndex,title.left(25));
    });
    connect(view,&WebPageView::titleChanged,[this,tabIndex](const QString &title){
        if(currentIndex()==tabIndex)
        {
            QString winTitle = title + " - " + fznavName;
            emit customWindowTitleChanged(winTitle);
        }
    });

}


BrowserTab* TabWidget::currentTab()
{
    return  (BrowserTab*) currentWidget();
}

void TabWidget::setupTabsBehavior()
{
    setMovable(true);
    setTabsClosable(true);
    setFocus(Qt::MouseFocusReason);
    resize(700,300);
}

QString TabWidget::themeDarkAurore(BrowserTab* btab)
{
    setStyleSheet("background-color:#253545;"
                  "color:#bea;");
    btab->setStyleSheet("QAction{border:1px red solid;}");
    btab->setStyleSheet("QLineEdit{padding-left:10px;"
                                   "border-radius:12%;"
                                   "height:25px;"
                                   "border:1px solid #06a58a}");
    return styleSheet();
}


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
    action->setShortcut(QKeySequence::Refresh);
    menu.exec(QCursor::pos());
}
