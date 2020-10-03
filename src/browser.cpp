#include "header/browser.h"

int Browser::nb_instances = 0;
QVector<Browser*> Browser::all_instances;
Browser::Browser(QWidget *parent, TabWidget* browserWindow) 
    : QMainWindow(parent)
    , tabwidget_instance(browserWindow)
{
    //p.load(QUrl("https://faouzimohamed.github.io/"));
    if(browserWindow==nullptr){
        newInstance(tabwidget_instance);
    }
    resize(900, 530);
    setDocumentMode(true);
    setContentsMargins(0,0,0,0);
    setWindowIcon(Fz::windowIcon());
}

TabWidget* Browser::newInstance(TabWidget* browser){
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
     b->newInstance(browser);
     b->show();
  });
  
  connect(tabWidget, &TabWidget::customWindowTitleChanged,
            [this](const QString &title){setWindowTitle(title);});
  
  instance_num = Browser::incrementNbInstances(this)-1;
  return tabWidget;
}


void Browser::closeEvent(QCloseEvent *event){
    event->accept();
    TabWidget* b =  qobject_cast<TabWidget*>(centralWidget());
    b->close();    
}

int Browser::count(){
    return Browser::nb_instances;
}

int Browser::incrementNbInstances(Browser* instance){
    Browser::all_instances.append(instance);
    return ++Browser::nb_instances;
}

int Browser::decrementNbInstances(Browser* instance){
    Browser::all_instances.removeOne(instance);
    return --Browser::nb_instances;
}

void Browser::removeInstance(Browser *instance)
{
    Browser::decrementNbInstances(instance);
    instance->close();
}

void Browser::closeAllInstances()
{
    for(auto each_instance: Browser::all_instances){
        Browser::removeInstance(each_instance);
    }
}

void Browser::closeAllInstancesExcept(Browser *instance)
{
    for(auto each_instance: Browser::all_instances){
        if(each_instance == instance){continue;}
        Browser::removeInstance(each_instance);
    }
}

void Browser::closeAllInstancesExcept(int instance_num)
{
    Browser* instance = Browser::all_instances.at(instance_num);
    Browser::closeAllInstancesExcept(instance);
}
