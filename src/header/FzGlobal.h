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



public : //Set Icons method
    static const QIcon    &windowIcon();
    static const QString& windowIconName();
    
    static const QIcon   &backIcon();
    static const QString &backIconName();
    
    static const QIcon   &forwardIcon();
    static const QString &forwardIconName();
    
    static const QIcon   &stopLoadIcon();
    static const QString &stopLoadIconName();
    
    static const QIcon   &reloadIcon();
    static const QString &reloadIconName();
    
    static const QIcon   &homeIcon();
    static const QString &homeIconName();
    
    static const QIcon   &submitIcon();
    static const QString &submitIconName();
    
};

#endif // GLOBALFUNCTIONS_H
