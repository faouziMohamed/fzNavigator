cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME FzNavigator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INSTALL_PREFIX _build/install)

# CMAKE_PREFIX_PATH variable need to be set to be able to compile the project
# It's recommended to set it in your IDE setting or use in the CLI
# Not directly in the CMakeLists.txt file. Here an example of setting up
# set(CMAKE_PREFIX_PATH  /media/faouzi/HOSTED/QT/Lin/5.15.2/gcc_64)

set(CMAKE_DIR ${CMAKE_PREFIX_PATH}/lib/cmake)
set(Qt5_DIR ${CMAKE_DIR}/Qt5)
set(Qt5Gui_DIR ${CMAKE_DIR}/Qt5Gui)
set(Qt5Core_DIR ${CMAKE_DIR}/Qt5Core)
set(Qt5Widgets_DIR ${CMAKE_DIR}/Qt5Widgets)
set(Qt5WebEngineWidgets_DIR ${CMAKE_DIR}/Qt5WebEngineWidgets)

set(MODULES_COMPONENTS Widgets WebEngineWidgets)
project(${PROJECT_NAME} LANGUAGES CXX)
find_package(QT NAMES Qt5 Qt6 COMPONENTS ${MODULES_COMPONENTS} REQUIRED)
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