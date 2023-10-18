# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: CC0-1.0

set(PUBLIC_HEADERS
    dsglobal.h
    dstypes.h
    pluginmetadata.h
    pluginloader.h
    pluginfactory.h
    applet.h
    containment.h
    corona.h
    quick/appletitem.h
    quick/containmentitem.h
    quick/panelview.h
    quick/qmlengine.h
)
add_library(dde-shell-frame SHARED
    ${PUBLIC_HEADERS}
    dstypes.cpp
    pluginmetadata.cpp
    pluginloader.cpp
    pluginfactory.cpp
    applet.cpp
    containment.cpp
    corona.cpp
    quick/appletitem.cpp
    quick/containmentitem.cpp
    quick/panelview.cpp
    quick/qmlengine.cpp
)

set_target_properties(dde-shell-frame PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    OUTPUT_NAME dde-shell
    EXPORT_NAME DDEShell
)
target_link_libraries(dde-shell-frame
PUBLIC
    Dtk${DTK_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
)
target_include_directories(dde-shell-frame INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/quick>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)
target_link_directories(dde-shell-frame INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${LIB_INSTALL_DIR}>
)

target_compile_definitions(dde-shell-frame
INTERFACE
    DDE_SHELL_PACKAGE_PATH_SUBPATH="dde-shell"
PRIVATE
    DDE_SHELL_QML_INSTALL_DIR="${CMAKE_INSTALL_PREFIX}/${QML_INSTALL_DIR}"
    DDE_SHELL_PLUGIN_INSTALL_DIR="${CMAKE_INSTALL_PREFIX}/${DDE_SHELL_PLUGIN_INSTALL_DIR}"
)

set(URI "org.deepin.ds")
add_library(dde-shell-plugin SHARED
    quick/qmlplugin.h
    quick/qmlplugin.cpp
    quick/qmldir
)

target_link_libraries(dde-shell-plugin
PUBLIC
    dde-shell-frame
)

string(REPLACE "." "/" URI_PATH ${URI})
set_target_properties(dde-shell-plugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/plugins/${URI_PATH}"
    OUTPUT_NAME dde-shell-plugin
)
set(QML_IMPORT_PATH "${PROJECT_BINARY_DIR}/plugins/${URI_PATH}" CACHE STRING "Qt Creator extra qml import paths")
add_custom_command(TARGET dde-shell-plugin
POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E  copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/quick/qmldir" "${PROJECT_BINARY_DIR}/plugins/${URI_PATH}"    #out-file
)

install(FILES ${PUBLIC_HEADERS} DESTINATION "${INCLUDE_INSTALL_DIR}")
install(TARGETS dde-shell-frame EXPORT DDEShellTargets DESTINATION "${LIB_INSTALL_DIR}")
install(EXPORT DDEShellTargets FILE DDEShellTargets.cmake DESTINATION "${CONFIG_INSTALL_DIR}")

install(TARGETS dde-shell-plugin EXPORT DDEShellTargets DESTINATION "${QML_INSTALL_DIR}/${URI_PATH}")
install(FILES quick/qmldir DESTINATION "${QML_INSTALL_DIR}/${URI_PATH}/")
