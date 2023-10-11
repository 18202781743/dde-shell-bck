// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.11
import QtQuick.Controls 2.4

import org.deepin.ds 1.0

AppletItem {
    width: 100
    height: 100
    Rectangle {
        anchors.fill: parent
        color: "green"
        Text {
            anchors.centerIn: parent
            text: "Hello world"
        }
    }
}