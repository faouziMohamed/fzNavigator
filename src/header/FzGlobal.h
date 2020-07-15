#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

class WebPage;
class TabWidget;
class EngineView;
#include <QtWidgets>
#include <QTranslator>
class FzGlobal;
typedef FzGlobal Fz;

class FzGlobal
{
public:
    FzGlobal();
    static const QString tr(const QAction* act);
    static bool currentActionIsNotNull(QAction *action);
    static bool isNotAnUrlSyntaxe(QString url);
};

#endif // GLOBALFUNCTIONS_H
