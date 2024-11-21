cmake_minimum_required(VERSION 3.27)
project(Carrier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "D:/QT/QTidea/6.6.1/mingw_64")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/res.qrc")
# 复制resource.dat到构建目录的bin文件夹
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/bin)
# 安装时复制整个resources目录到安装目录的bin文件夹
install(DIRECTORY resources DESTINATION bin)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Carrier  main.cpp
        src/dresswin.cpp
        include/dresswin.h
        ui/ui_dresswin.h
        ui/dresswin.ui
        #============
        src/carrier.cpp
        include/carrier.h
        ui/ui_carrier.h
        ui/carrier.ui
        #============
        src/setwin.cpp
        include/setwin.h
        ui/ui_setwin.h
        ui/setwin.ui
        #============
        resources/res.qrc
        ${app_icon_resource_windows}
)
target_link_libraries(Carrier
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
