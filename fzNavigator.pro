######################################################################
# Automatically generated by qmake (3.1) Wed Feb 12 12:00:25 2020
######################################################################

TEMPLATE = app
TARGET = fzNavigator
INCLUDEPATH += .
QT += core webenginewidgets gui

# Input
SOURCES += main.cpp \
    src/MainWindow.cpp \
    src/webEngineTools.cpp

HEADERS += \
    src/header/MainWindow.h\
    src/header/webEngineTools.h

TRANSLATIONS = assets/lang/fzNavigator_fr.ts

RESOURCES += assets/Pictures.qrc
RC_ICONS = assets/web.ico

