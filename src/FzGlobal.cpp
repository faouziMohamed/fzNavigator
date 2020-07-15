#include "header/FzGlobal.h"
FzGlobal::FzGlobal()
{

}

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
