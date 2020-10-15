#include "header/FzGlobal.h"


FzGlobal::FzGlobal()
{
    
}

const QIcon& FzGlobal::windowIcon()
{
    static QIcon FZ_WIN_ICON(ICON_PATH+"web.png");
    return FZ_WIN_ICON;
}
const QString &FzGlobal::windowIconName()
{
    const static QString path(ICON_PATH+"web.png");
    return path;
}


const QIcon &FzGlobal::backIcon()
{
    static QIcon BACK_ICON(ICON_PATH+"left_full.svg");
    return BACK_ICON;
}
const QString &FzGlobal::backIconName()
{
    const static QString path(ICON_PATH+"left_full.svg");
    return path;
}


const QIcon &FzGlobal::forwardIcon()
{
    static QIcon FORWARD_ICON(ICON_PATH+"right_empty.svg");
    return FORWARD_ICON;
}
const QString &FzGlobal::forwardIconName()
{
    const static QString path(ICON_PATH+"right_empty.svg");
    return path;
}


const QIcon &FzGlobal::stopLoadIcon()
{
    static QIcon STOP_LOAD_ICON(ICON_PATH+"cancel.svg");
    return STOP_LOAD_ICON;
}
const QString &FzGlobal::stopLoadIconName()
{ //://fznavigator_icones/menu.png
    const static QString path(ICON_PATH+"cancel.svg");
    return path;
}



const QIcon &FzGlobal::reloadIcon()
{
    static QIcon RELOAD_ICON(ICON_PATH+"Reload.svg");
    return RELOAD_ICON;
}
const QString &FzGlobal::reloadIconName()
{
    const static QString path(ICON_PATH+"Reload.svg");
    return path;
}


const QIcon &FzGlobal::homeIcon()
{
    static QIcon HOME_ICON(ICON_PATH+"home_43.svg");
    return HOME_ICON;
}
const QString &FzGlobal::homeIconName()
{
    const static QString path(ICON_PATH+"home_43.svg");
    return path;
}


const QIcon &FzGlobal::submitIcon()
{
    static QIcon SUBMIT_ICON(ICON_PATH+"search_62.svg");
    return SUBMIT_ICON;
}
const QString &FzGlobal::submitIconName()
{
    const static QString path(ICON_PATH+"search_62.svg");
    return path;
}


const QIcon &FzGlobal::dangerIcon()
{
    static QIcon SUBMIT_ICON(ICON_PATH+"danger.svg");
    return SUBMIT_ICON;
}
const QString &FzGlobal::dangerIconName()
{
    const static QString path(ICON_PATH+"danger.svg");
    return path;
}

const QIcon &FzGlobal::loaderIcon()
{
    static QIcon SUBMIT_ICON(ICON_PATH+"loader.gif");
    return SUBMIT_ICON;
}
const QString &FzGlobal::loaderIconName()
{
    const static QString path(ICON_PATH+"loader.gif");
    return path;
}

const QIcon &FzGlobal::defaultFavIcon()
{
    static QIcon SUBMIT_ICON(ICON_PATH+"web.png");
    return SUBMIT_ICON;
}
const QString &FzGlobal::defaultFavIconName()
{
    const static QString path(ICON_PATH+"web.png");
    return path;
}

const QIcon &FzGlobal::menuOptIcon()
{
    static QIcon STOP_LOAD_ICON(ICON_PATH+"menu.png");
    return STOP_LOAD_ICON;
}
const QString &FzGlobal::menuOptIconName()
{ //:/fznavigator_icones/menu.png
    const static QString path(ICON_PATH+"menu.png");
    return path;
}




/**
* @brief return the text contained in the action, the text is translatable
*/
const QString FzGlobal::tr(const QAction *act)
{
    return QTranslator::tr(qPrintable(act->text()));
}

bool FzGlobal::currentActionIsNotNull(QAction *action){
    return action != nullptr;
}

void FzGlobal::addActionsToTheToolbar(QToolBar* aToolbar,...)
{
    va_list listOfvariableArguments;
    va_start(listOfvariableArguments, aToolbar);
    QAction *currentAction = va_arg(listOfvariableArguments, QAction *);
    while(Fz::currentActionIsNotNull(currentAction))
    {
        aToolbar->addAction(currentAction);
        currentAction = va_arg(listOfvariableArguments, QAction *);
    }
    va_end(listOfvariableArguments);
}

bool FzGlobal::isNotAnUrlSyntaxe(QString url)
{
    QChar dot = '.', space = ' ';
    return  url.contains(space)|| (!url.contains(dot));
}
