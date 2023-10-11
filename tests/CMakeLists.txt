# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: CC0-1.0

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Gui DBus)
find_package(DtkCore REQUIRED)
find_package(DtkGui REQUIRED)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Test)

# generate moc_predefs.h
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_COMPILER_PREDEFINES ON)

ADD_EXECUTABLE(ds-test
    main.cpp
)

target_include_directories(ds-test PUBLIC
    ../app
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(ds-test PUBLIC
    dde-shell-frame
    Qt5::Test
    -lgtest
    -lpthread
)
