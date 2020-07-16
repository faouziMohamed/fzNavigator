#include "header/tabwidget.h"

TabWidget::TabWidget(QWebEngineProfile *profile, QWidget * parent)
    : QTabWidget(parent)
{
    tab = new BrowserTab(this,profile);
    setupTabsBehavior();
    themeDarkAurore();
}

void TabWidget::setupTabsBehavior()
{
    setMovable(true);
    setTabsClosable(true);
    setFocus(Qt::MouseFocusReason);
    resize(700,300);
}

QString TabWidget::themeDarkAurore()
{
    this->addTab(tab,"About:Blank");
    setStyleSheet("background-color:#253545;"
                  "color:#bea;");
    tab->m_urlField->setStyleSheet("padding-left:10px;"
                                   "border-radius:12%;"
                                   "height:25px;"
                                   "border:1px solid #555");
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
