// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.15

import org.deepin.ds 1.0
import org.deepin.dtk 1.0 as D

Window {
    id: root
    visible: true
    width: Screen.width
    height: 200
    D.DWindow.enabled: true
    Panel.position: Types.TopPositioned

    Control {
        anchors.fill: parent
        padding: 20
        contentItem: Applet.applets[0]
        background: Rectangle {
            color: "plum"
            opacity: 0.8
        }
    }
}
