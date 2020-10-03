#include "header/FzGlobal.h"


FzGlobal::FzGlobal()
{
    
}

const QIcon& FzGlobal::windowIcon()
{
    static QIcon FZ_WIN_ICON(":/fznavigator_icones/web.png");
    return FZ_WIN_ICON;
}
const QString &FzGlobal::windowIconName()
{
    const static QString path(":/fznavigator_icones/web.png");
    return path;
}


const QIcon &FzGlobal::backIcon()
{
    static QIcon BACK_ICON(":/fznavigator_icones/left_full.svg");
    return BACK_ICON;
}
const QString &FzGlobal::backIconName()
{
    const static QString path(":/fznavigator_icones/left_full.svg");
    return path;
}


const QIcon &FzGlobal::forwardIcon()
{
    static QIcon FORWARD_ICON(":/fznavigator_icones/right_empty.svg");
    return FORWARD_ICON;
}
const QString &FzGlobal::forwardIconName()
{
    const static QString path(":/fznavigator_icones/right_empty.svg");
    return path;
}


const QIcon &FzGlobal::stopLoadIcon()
{
    static QIcon STOP_LOAD_ICON(":/fznavigator_icones/cancel.svg");
    return STOP_LOAD_ICON;
}
const QString &FzGlobal::stopLoadIconName()
{
    const static QString path(":/fznavigator_icones/cancel.svg");
    return path;
}



const QIcon &FzGlobal::reloadIcon()
{
    static QIcon RELOAD_ICON(":/fznavigator_icones/Reload.svg");
    return RELOAD_ICON;
}
const QString &FzGlobal::reloadIconName()
{
    const static QString path(":/fznavigator_icones/Reload.svg");
    return path;
}


const QIcon &FzGlobal::homeIcon()
{
    static QIcon HOME_ICON(":/fznavigator_icones/home_43.svg");
    return HOME_ICON;
}
const QString &FzGlobal::homeIconName()
{
    const static QString path(":/fznavigator_icones/home_43.svg");
    return path;
}


const QIcon &FzGlobal::submitIcon()
{
    static QIcon SUBMIT_ICON(":/fznavigator_icones/search_62.svg");
    return SUBMIT_ICON;
}
const QString &FzGlobal::submitIconName()
{
    const static QString path(":/fznavigator_icones/search_62.svg");
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
bool FzGlobal::isNotAnUrlSyntaxe(QString url)
{
    QChar dot = '.', space = ' ';
    return  url.contains(space)|| (!url.contains(dot));
}
