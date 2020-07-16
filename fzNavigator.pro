######################################################################
# Automatically generated by qmake (3.1) Sun Jul 12 23:40:58 2020
######################################################################

TEMPLATE = app
TARGET = fzNavigator
INCLUDEPATH += .
QT += core webenginewidgets gui \
    widgets

DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += \
    src/header/FzGlobal.h \
    src/header/browsertab.h \
    src/header/tabwidget.h \
    src/header/webPageView.h \
    src/header/webpage.h

SOURCES += \
	main.cpp \
	src/FzGlobal.cpp \
	src/browsertab.cpp \
	src/tabwidget.cpp \
	src/webPageView.cpp \
	src/webpage.cpp

RESOURCES += assets/Pictures.qrc
TRANSLATIONS += assets/lang/fzNavigator_fr.ts
RC_ICONS = assets/web.ico
