#include "MainWindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent)
{
    createMenu();
    setBehaviorForTabs();
    createInitialTab();
    applyAndFinalizeTabsConfigurationsToTheCentralView();
}
void MainWindow::createMenu()
{
    createTheMenuFile();
    createTheMenuNavigation();
    createTheMenuHelp();
    menuBar()->setVisible(true);
}
void MainWindow::setBehaviorForTabs()
{
    tabContainer = new QTabWidget();
    tabContainer->setTabShape(QTabWidget::Triangular);
    tabContainer->setTabsClosable(true);
    tabContainer->setMovable(true);
    connect(tabContainer,
            SIGNAL(tabCloseRequested(int)),this,
            SLOT(removeTab(int)));

    connect(tabContainer,
            SIGNAL(currentChanged(int)), this,
            SLOT(switchToAnOtherTab(int)));
}
void MainWindow::createInitialTab(){
    addNewTab();
}
void MainWindow::applyAndFinalizeTabsConfigurationsToTheCentralView(){
    setCentralWidget(tabContainer);
    setWindowIcon(QIcon(":/fznavigator_icones/web.png"));
    this->resize(1024,650);
}
void MainWindow::createTheMenuFile(){
    creatingTheMenuFileItems();
    addShortcutInMenuFile();
    createConnectionInMenuFile();
}
void MainWindow::createTheMenuNavigation(){
    navigationMenu = menuBar()->addMenu(tr("Navigation"));
    m_previousAction = new QAction(QIcon(":/fznavigator_icones/prev.png"),   tr("Back"));
    m_nextPageAction = new QAction(QIcon(":/fznavigator_icones/next.png"),   tr("Forward"));
    m_refreshAction  = new QAction(QIcon(":/fznavigator_icones/refresh.png"),tr("Reload"));
    m_stopAction     = new QAction(QIcon(":/fznavigator_icones/stop.png"),   tr("Stop"));
    m_goAction       = new QAction(QIcon(":/fznavigator_icones/go.png"),     tr("Go"));

    addMultipleActionsToTheMenu(navigationMenu,m_previousAction,
                                m_nextPageAction,m_refreshAction,
                                m_stopAction,m_goAction,nullptr);
}
void MainWindow::createTheMenuHelp(){
    helpMenu = menuBar()->addMenu(tr("Help"));
}
void MainWindow::creatingTheMenuFileItems(){
    fileMenu = menuBar()->addMenu(tr("File"));
    newWindowsAction   = new QAction(tr("New window"), menuBar());
    exitAction         = new QAction(tr("Quit"),       menuBar());
    newTabAction       = new QAction(tr("New tab"),    menuBar());
    closeTabAction     = new QAction(tr("Close tab"),  menuBar());

    addMultipleActionsToTheMenu (fileMenu, newWindowsAction,
                                 exitAction, newTabAction,
                                 closeTabAction,nullptr);
}
/**
 * This function get variable number of arguments using the C syntax
**/
void MainWindow::addMultipleActionsToTheMenu(QMenu* menuOfActions,...)
{
    va_list listOfvariableArguments;
    va_start(listOfvariableArguments, menuOfActions);
    QAction *currentAction = va_arg(listOfvariableArguments, QAction *);
    while(currentActionIsNotNull(currentAction))
    {
        menuOfActions->addAction(currentAction);
        currentAction = va_arg(listOfvariableArguments, QAction *);
    }
    va_end(listOfvariableArguments);
}
bool MainWindow::currentActionIsNotNull(QAction *action){
    return action != nullptr;
}
void MainWindow::createConnectionInMenuFile()
{
    connect(newWindowsAction,SIGNAL(triggered()),this,SLOT(openNewWindow()));
    connect(closeTabAction,SIGNAL(triggered()),this,SLOT(removeTab()));
    connect(newTabAction,SIGNAL(triggered()),this,SLOT(addNewTab()));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
}
void MainWindow::addShortcutInMenuFile(){
    newWindowsAction->setShortcut(QKeySequence(QKeySequence::New));
    closeTabAction->setShortcut(QKeySequence("CTRL+W"));
    newTabAction->setShortcut(QKeySequence(QKeySequence::AddTab));
    exitAction->setShortcut(QKeySequence("CTRL+Q"));
}
void MainWindow::addNewTab()
{
    QWebEngineView *webPage = newTab();
   connect( webPage,SIGNAL(titleChanged(QString)), this,
                    SLOT(changeTheWindowTitle(QString)));
}
QWebEngineView *MainWindow::newTab()
{
    WebEngineTools *engineContainer = new WebEngineTools(this);
    int indexOfNewTab = tabContainer->addTab(engineContainer,tr("About:blank"));
    switchToTheTabNumber(indexOfNewTab);
    return engineContainer->getWebEngine ();
}
void MainWindow::switchToTheTabNumber(int indexOfTab){
    tabContainer->setCurrentIndex(indexOfTab);
}
void MainWindow::removeTab(int currentTab)
{
    if(numberOfTab()<=1)
        closeThisWindow();
    else
    {
        if(currentTab==-1){
            currentTab = tabContainer->currentIndex();
        }
        tabContainer->removeTab(currentTab);
    }
}

void MainWindow::openNewWindow()
{
    //nullptr mean that this new window has no parent
    MainWindow *window = new MainWindow(nullptr);
    window->show();
}

void MainWindow::closeThisWindow(){
    this->close();
}

WebEngineTools *MainWindow::currentWindow()
{
    return (WebEngineTools*)(tabContainer->currentWidget());
}
QWebEngineView *MainWindow::currentPage()
{
    return currentWindow()->centralWidget()->findChild<QWebEngineView *>();
}

int MainWindow::numberOfTab(){
    return tabContainer->count();
}
void MainWindow::switchToAnOtherTab(int)
{
    QString title = currentWindow()->title();
   if(title.isEmpty())
        this->setWindowTitle(tr("FzNavigator"));
   else
        this->setWindowTitle(title + tr(" - fzNavigator"));
}
void MainWindow::changeTheWindowTitle(QString title)
{
    //truncate the title if it too long
    QString newTitle = title;
    if(title.size() > 25)
    {
        newTitle = title.left(25) + "...";
    }
    int index = tabContainer->currentIndex();

    tabContainer->setTabText(index,newTitle);
    this->setWindowTitle(newTitle);
}





/*Automated function to add Actions to the main Menu*/
void MainWindow::addMultipleActionsToTheMenu(QString name, QMenu* menuOfActions,
                                             QList<QAction *> menuActions)
{
    menuOfActions = menuBar()->addMenu(tr(name.toStdString().data()));
    for (int i=0;i<menuActions.size();++i) {
        menuOfActions->addAction(menuActions.at(i));
    }
}

MainWindow::~MainWindow()
{
      delete newWindowsAction;
      delete closeTabAction;
      delete exitAction;
      delete newTabAction;
    delete fileMenu;

    delete  helpMenu;

    if(m_previousAction!=nullptr)
    {
        delete m_previousAction;
        delete m_nextPageAction;
        delete m_refreshAction;
        delete m_stopAction;
        delete m_goAction;
    }

    if(tabContainer!=nullptr)
    {
        delete tabContainer;
    }
}
