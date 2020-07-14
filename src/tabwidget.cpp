#include "header/tabwidget.h"
#include "src/header/webpage.h"
#include "src/header/engineview.h"

TabWidget::TabWidget(QWidget * parent)
    : QTabWidget(parent)
{
    QTabBar *tabBar = this->tabBar();
    tabBar->setTabsClosable(true);
    tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    tabBar->setMovable(true);
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBar, SIGNAL(customContextMenuRequested(int)), this,
                    SLOT(handleContextMenuRequested(int)));

    EngineView *view = new EngineView(0);
    QWebEngineProfile *profile = new QWebEngineProfile;
    WebPage *web = new WebPage(view, profile);
    web->load(QUrl("http://duckduckgo.com/"));
    view->setPage(web);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(view);

    this->resize(1024,768);
}

void TabWidget::handleContextMenuRequested(const QPoint &pos)
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
