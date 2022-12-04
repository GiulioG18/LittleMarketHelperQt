cmake_minimum_required(VERSION 3.5)

project(LittleMarketHelper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES LittleMarketHelper_it_IT.ts)

set(PROJECT_SOURCES
        main.cpp
        littlemarkethelper.h littlemarkethelper.cpp littlemarkethelper.ui
        utils.h
        portfolio.h portfolio.cpp
        portfolioinitializationdialog.h portfolioinitializationdialog.cpp portfolioinitializationdialog.ui
        parser.h parser.cpp
        product.h product.cpp
        portfolioupdater.h portfolioupdater.cpp
        portfoliotablewidget.h portfoliotablewidget.cpp
        mainbutton.h mainbutton.cpp
        initialize.cpp edit.cpp calibrate.cpp history.cpp help.cpp about.cpp exit.cpp
        productitem.h productitem.cpp
        portfolioeditor.h portfolioeditor.cpp
        portfolioeditortablewidget.h portfolioeditortablewidget.cpp
        portfoliovaluelabel.h portfoliovaluelabel.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LittleMarketHelper
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LittleMarketHelper APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(LittleMarketHelper SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LittleMarketHelper
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(LittleMarketHelper PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Link test
target_link_libraries(LittleMarketHelper PRIVATE $ENV{OR_TOOLS}/TestLib.lib)
target_include_directories(LittleMarketHelper PRIVATE $ENV{OR_TOOLS}/)

set_target_properties(LittleMarketHelper PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS LittleMarketHelper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LittleMarketHelper)
endif()
