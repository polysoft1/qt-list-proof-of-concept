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


qt5_add_resources(RESOURCE_ADDED ${CMAKE_SOURCE_DIR}/icons.qrc)
set(AUTORCC_OPTIONS ON)

set(SOURCE_FILES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    message.cpp
    messagegroup.cpp
    MessageGroupModel.h
    MessageGroupModel.cpp
    MessageModel.h
    MessageModel.cpp)

if(ANDROID)
  add_library(TimelineExperiment SHARED
    ${SOURCE_FILES} ${RESOURCE_ADDED}
  )
else()
  add_executable(TimelineExperiment
    ${SOURCE_FILES} ${RESOURCE_ADDED}
  )
endif()

target_link_libraries(TimelineExperiment PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::QuickWidgets)

set(QML_FILES Timeline.qml ScrollHelper.qml)
set(FILES_TO_COPY "")
foreach(item ${QML_FILES})
    add_custom_command(TARGET TimelineExperiment POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/qml/${item} ${CMAKE_BINARY_DIR}/qml/${item})
endforeach()
