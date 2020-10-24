cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODULES_COMPONENTS Widgets WebEngineWidgets)

project(${PROJECT_NAME} LANGUAGES CXX)
find_package(QT NAMES Qt6 Qt5 COMPONENTS ${MODULES_COMPONENTS} REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${MODULES_COMPONENTS} REQUIRED)

set(SOURCE_FILES
    main.cpp
    src/browser.cpp
    src/FzGlobal.cpp
    src/browsertab.cpp
    src/tabwidget.cpp
    src/webpage.cpp
    src/webPageView.cpp
)

set(HEADER_FILES
    src/header/browser.h
    src/header/browsertab.h
    src/header/FzGlobal.h
    src/header/tabwidget.h
    src/header/webpage.h
    src/header/webPageView.h
)

set(QRC_FILES assets/Pictures.qrc)

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${QRC_FILES} ${HEADER_FILES} )

target_link_libraries( ${PROJECT_NAME} Qt5::Widgets Qt5::WebEngineWidgets )