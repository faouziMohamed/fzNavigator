#include "header/browser.h"

Browser::Browser(QWidget *parent, TabWidget* browserWindow) 
    : QMainWindow(parent)
    , instance(browserWindow)
{
    //p.load(QUrl("https://faouzimohamed.github.io/"));
    if(browserWindow==nullptr){
        newBrowserinstance(instance);
    }
    resize(900, 530);
    setDocumentMode(true);
    setContentsMargins(0,0,0,0);
    setWindowIcon(QIcon(":/fznavigator_icones/web.png"));
}

TabWidget* Browser::newBrowserinstance(TabWidget* browser){
  TabWidget *tabWidget;
  if(browser==nullptr){
      QWebEngineProfile *profil = QWebEngineProfile::defaultProfile();
      tabWidget = new TabWidget(profil, TabsBehavior::NewTab, this);
  }
  else{
      tabWidget = browser;
  }

  setCentralWidget(tabWidget);
  connect(tabWidget, &TabWidget::windowRequired, this, [](TabWidget* browser){
     Browser *b = new Browser(nullptr);
     b->newBrowserinstance(browser);
     b->show();
  });
  return tabWidget;
}


void Browser::closeEvent(QCloseEvent *event){
    event->accept();
    TabWidget* b =  qobject_cast<TabWidget*>(centralWidget());
    b->close();    
}
