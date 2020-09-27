#include "header/FzGlobal.h"
FzGlobal::FzGlobal()
{

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
    return  url.contains(space)||
            (!url.contains(dot));
}
