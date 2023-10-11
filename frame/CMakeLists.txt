# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: CC0-1.0


add_library(dde-shell-frame SHARED
    pluginmetadata.h
    pluginmetadata.cpp
    pluginloader.h
    pluginloader.cpp
    pluginfactory.h
    pluginfactory.cpp
    applet.h
    applet.cpp
    containment.h
    containment.cpp
    corona.h
    corona.cpp
    quick/appletitem.h
    quick/appletitem.cpp
    quick/containmentitem.h
    quick/containmentitem.cpp
    quick/panelview.h
    quick/panelview.cpp
    quick/qmlengine.h
    quick/qmlengine.cpp

)

set_target_properties(dde-shell-frame PROPERTIES OUTPUT_NAME dde-shell)
target_link_libraries(dde-shell-frame
PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
)
target_include_directories(dde-shell-frame INTERFACE
    ${CMAKE_SOURCE_DIR}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/quick>
)
target_link_directories(dde-shell-frame INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${LIB_INSTALL_DIR}>
)

target_compile_definitions(dde-shell-frame INTERFACE
    DDE_SHELL_PACKAGE_PATH_SUBPATH="dde-shell"
)
