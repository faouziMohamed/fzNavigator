#include "header/webpage.h"
#include <QMessageBox>
WebPage::WebPage(QObject *parent, QWebEngineProfile *profil)
    : QWebEnginePage(profil, parent)
{

}

