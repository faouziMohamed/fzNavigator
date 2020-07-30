#include "header/tabwidget.h"

TabWidget::TabWidget(QWebEngineProfile *profile, QWidget * parent)
    : QTabWidget(parent)
    , fznavName("Fz Navigator")
    , newTabTitle("About:Blank - Fz Navigo")
    , m_profile(profile)
{
    addNewTab();
    setupTabsBehavior();
    setUpMainConnexions();
}

void TabWidget::setUpMainConnexions()
{
    QShortcut *newtabShortcut = new QShortcut(QKeySequence::AddTab,this);
    connect(newtabShortcut,SIGNAL(activated()),this,SLOT(addNewTab()));
    connect(this,&QTabWidget::currentChanged,[this](int index){
        if(index!=-1){
            QString winTitle = tabText(index) + " - " + fznavName;
            emit customWindowTitleChanged(winTitle);
        }
    });

    connect(this,&TabWidget::customWindowTitleChanged,
            [this](const QString &title){setWindowTitle(title);});
    connect(this,&TabWidget::tabCloseRequested,[this](int index){
        removeTab(index);
        if(count()>0){
            currentTab()->setFocus();
        }
        else
        {
            this->close();
        }

    });
}



BrowserTab* TabWidget::addNewTab()
{
   BrowserTab *newTab = new BrowserTab(this,m_profile);
   WebPageView* view = newTab->view();
   int index = addTab(newTab,newTabTitle);
   setCurrentIndex(index);
   setTabIcon(index,view->favIcon());

   setUpTabConnexions(newTab);
   setUserTheme("://style/userTheme.css");
   return newTab;
}

void TabWidget::setUpTabConnexions(BrowserTab* newTab)
{
    WebPageView *view = newTab->view();
    //int index = indexOf(newTab);
    connect(newTab,&BrowserTab::favIconSent,[this,newTab](const QIcon& icon){
        setTabIcon(indexOf(newTab),icon);});

    connect(view,&WebPageView::titleChanged,[this,newTab](const QString &title){
        setTabText(indexOf(newTab),title.left(25));
        setTabToolTip(indexOf(newTab),title);
    });
    connect(view,&WebPageView::titleChanged,[this, newTab](const QString &title){
        if(currentIndex()==indexOf(newTab)){
            QString winTitle = title + " - " + fznavName;
            emit customWindowTitleChanged(winTitle);
        }
    });
}


BrowserTab* TabWidget::currentTab()
{
    return  qobject_cast<BrowserTab*>(currentWidget());
}

BrowserTab* TabWidget::widget(int index)
{
    return  qobject_cast<BrowserTab*>(QTabWidget::widget(index));
}

void TabWidget::setupTabsBehavior()
{
    setMovable(true);
    setTabsClosable(true);
    setFocus(Qt::MouseFocusReason);
    resize(900,530);
    this->setWindowIcon(QIcon(":/fznavigator_icones/web.png"));
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
