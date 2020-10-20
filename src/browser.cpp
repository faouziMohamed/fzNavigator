#include "header/browser.h"

QVector<Browser*> Browser::all_instances;

Browser::Browser(TabWidget* browserWindow, QWidget *parent) 
    : QMainWindow(parent)
    , tabwidget_instance(browserWindow)
{
    //load(QUrl("https://faouzimohamed.github.io/"));
    newInstance(tabwidget_instance);
    configureWindow();
}

Browser::Browser() : Browser(nullptr) { }

void Browser::configureWindow()
{
    resize(900, 530);
    setDocumentMode(true);
    setContentsMargins(0,0,0,0);
    setWindowIcon(Fz::windowIcon());    
}


TabWidget* Browser::newInstance(TabWidget* tabwidget_instance){
  TabWidget *tabWidget;
  if(tabwidget_instance==nullptr){
      QWebEngineProfile *profil = QWebEngineProfile::defaultProfile();
      tabWidget = new TabWidget(profil, TabsBehavior::NewTab, this);
  }
  else{
      tabWidget = tabwidget_instance;
  }

  setCentralWidget(tabWidget);

  connect(tabWidget, &TabWidget::windowRequired, this, [](TabWidget* received_tabwidget){
     Browser *b = new Browser(received_tabwidget, nullptr);
     b->show();
  });
  
  connect(tabWidget, &TabWidget::exitWindowsRequested, this, [](){
    Browser::closeAllInstances();
  });
  
  connect(tabWidget, &TabWidget::customWindowTitleChanged,
            [this](const QString &title){setWindowTitle(title);});
  
  //Memorise all instance of Browser in a vector,
  //So later we can tweak them and reuse them separately
  Browser::addInstance(this);
  return tabWidget;
}


void Browser::closeEvent(QCloseEvent *event){
    event->accept();
    TabWidget* b = qobject_cast<TabWidget*>(centralWidget());
    b->close();
    Browser::removeInstance(this);
    
    //Browser::deleteInstance(this);
}

int Browser::count(){
    return Browser::all_instances.size();
}

int Browser::addInstance(Browser* instance){
    Browser::all_instances.append(instance);
    return Browser::count();
}

int Browser::removeInstance(Browser* instance){
    Browser::all_instances.removeOne(instance);
    return Browser::count();
}

void Browser::deleteInstance(Browser *instance)
{
    Browser::removeInstance(instance);
    instance->close();
}

void Browser::closeAllInstances()
{
    foreach(auto each_instance, Browser::all_instances){
        Browser::deleteInstance(each_instance);
    }
}

void Browser::closeAllInstancesExcept(Browser *instance)
{
    foreach(auto each_instance, Browser::all_instances){
        if(each_instance == instance){continue;}
        Browser::deleteInstance(each_instance);
    }
}

void Browser::closeAllInstancesExcept(int instance_num)
{
    Browser* instance = Browser::all_instances.at(instance_num);
    Browser::closeAllInstancesExcept(instance);
}
