# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: CC0-1.0

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Gui Widgets)
find_package(Dtk${DTK_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_executable(dde-shell
    main.cpp
)

target_link_libraries(dde-shell PRIVATE
    dde-shell-frame
    Qt5::Widgets
    Dtk::Gui
)

install(TARGETS dde-shell DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

