#include "header/tabwidget.h"
#include "src/header/webpage.h"
#include "src/header/engineview.h"

TabWidget::TabWidget(QWidget * parent)
    : QTabWidget(parent)
{
    EngineView *view = new EngineView(0);
    QWebEngineProfile *profile = new QWebEngineProfile;
    WebPage *web = new WebPage(view, profile);
    web->load(QUrl("http://duckduckgo.com/"));
    view->setPage(web);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(view);

    this->resize(1024,768);
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
