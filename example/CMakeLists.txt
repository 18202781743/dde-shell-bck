# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: GPL-3.0-or-later

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Gui)

add_subdirectory(applet-example)
add_subdirectory(applet-example-data)
add_subdirectory(containment-example)
add_subdirectory(corona-example)
