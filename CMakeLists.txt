cmake_minimum_required(VERSION 3.5)

project(TimelineExperiment LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS QuickWidgets Widgets Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS QuickWidgets Widgets Gui REQUIRED)

if(ANDROID)
  add_library(TimelineExperiment SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    message.cpp
    MyListModel.h
    MyListModel.cpp
  )
else()
  add_executable(TimelineExperiment
    main.cpp
    mainwindow.cpp
    mainwindow.h
    message.cpp
    MyListModel.h
    MyListModel.cpp
  )
endif()

target_link_libraries(TimelineExperiment PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::QuickWidgets)

add_custom_command(TARGET TimelineExperiment POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/qml/Timeline.qml
    ${CMAKE_BINARY_DIR}/qml/Timeline.qml)

add_custom_command(TARGET TimelineExperiment
                     PRE_BUILD
                    COMMAND echo "This is pre build "
        )
add_custom_command(TARGET TimelineExperiment
                    POST_BUILD
                   COMMAND echo "This is post build"
        )
