cmake_minimum_required(VERSION 3.5)
project(project_cpp)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 23)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia MultimediaWidgets)


include_directories(src ui)

set(UI_FILES
        ui/MainWindow.ui
        ui/VideoPlayerWidget.ui
        ui/TimelineWidget.ui
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(HEADERS
        src/MainWindow.h
        src/VideoPlayerWidget.h
        src/TimelineWidget.h
        src/TextOverlayWidget.h
)

add_executable(project_cpp
        src/main.cpp
        src/MainWindow.cpp
        src/VideoPlayerWidget.cpp
        src/TimelineWidget.cpp
        src/TextOverlayWidget.cpp
        src/FFmpegHandler.cpp
        src/FFmpegHandler.h
        src/Track.h
        src/Track.cpp
        src/Track.cpp
        src/VideoEditor.cpp
        src/FileImportWidget.cpp
        src/FileImportWidget.h
)

set(CMAKE_PREFIX_PATH "D:/QT/6.7.2/mingw_64")

target_include_directories(project_cpp PRIVATE ${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS})

target_link_libraries(project_cpp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)
