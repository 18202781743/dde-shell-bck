# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: GPL-3.0-or-later

qt_add_resources(RESOURCES
    image.qrc
)
add_library(osdcorona SHARED
    osdcorona.cpp
    osdcorona.h
    ${RESOURCES}
    test.sh
)

target_link_libraries(osdcorona PRIVATE
    dde-shell-frame
    Qt${QT_MAJOR_VERSION}::DBus
)

ds_install_package(PACKAGE org.deepin.ds.osd TARGET osdcorona)

#add_subdirectory(default)
#add_subdirectory(audio)
add_subdirectory(displaymode)
