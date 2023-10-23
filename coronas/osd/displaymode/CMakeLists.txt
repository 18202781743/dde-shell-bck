# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(osd-displaymode SHARED
    displaymodeapplet.cpp
    displaymodeapplet.h
)

target_link_libraries(osd-displaymode PRIVATE
    dde-shell-frame
)

ds_install_package(PACKAGE org.deepin.ds.osd.displaymode TARGET osd-displaymode)
