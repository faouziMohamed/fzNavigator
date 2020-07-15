#include "header/tabwidget.h"

TabWidget::TabWidget(QWebEngineProfile *profil, QWidget * parent)
    : QTabWidget(parent)
{
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
