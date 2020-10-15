#include "header/browser.h"

int Browser::nb_instances = 0;
QVector<Browser*> Browser::all_instances;
Browser::Browser(QWidget *parent, TabWidget* browserWindow) 
    : QMainWindow(parent)
    , tabwidget_instance(browserWindow)
{
    //load(QUrl("https://faouzimohamed.github.io/"));
    if(browserWindow==nullptr){
        newInstance(tabwidget_instance);
    }
    
    resize(900, 530);
    setDocumentMode(true);
    setContentsMargins(0,0,0,0);
    setWindowIcon(Fz::windowIcon());
    //QMessageBox::information(this, "Test", QString().number(Browser::nb_instances));
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
     Browser *b = new Browser(nullptr);
     b->newInstance(received_tabwidget);
     b->show();
  });
  
  connect(tabWidget, &TabWidget::customWindowTitleChanged,
            [this](const QString &title){setWindowTitle(title);});
  
  //Memorise all instance of Browser in a vector,
  //So later we can tweak them and reuse them separately
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
