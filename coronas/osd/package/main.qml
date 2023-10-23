// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import org.deepin.ds 1.0
import org.deepin.dtk 1.0 as D

Window {
    id: root
    visible: true
    D.DWindow.enabled: true
    width: content.width
    height: content.height || 60
//    DLayerShellWindow.anchors: DLayerShellWindow.AnchorTop
//    DLayerShellWindow.layer: DLayerShellWindow.LayerTop

    D.Control {
        id: content
        anchors.fill: parent
        contentItem: Repeater {
            id: repeater
            model: Applet.appletItems
            delegate: Loader {
                id: loader
                anchors.fill: parent
                active: modelData.match(Applet.osdType)
                visible: active
                sourceComponent: Control {
                    id: impl
                    anchors.fill: parent
                    contentItem: modelData
                }
            }
        }

        background: Rectangle {
            color: "gray"
        }
    }
    Timer {
        running: true
        interval: 2000
        repeat: true
        onTriggered: {

                console.log("dddddddddddddddd", repeater.height, root.height)
        }
    }
}
