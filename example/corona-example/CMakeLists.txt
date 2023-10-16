# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: GPL-3.0-or-later

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Gui)

add_library(ds-corona-example SHARED
    examplecorona.cpp
    examplecorona.h
)

target_link_libraries(ds-corona-example PRIVATE
    dde-shell-frame
)

ds_install_package(PACKAGE org.deepin.ds.corona-example TARGET ds-corona-example)
