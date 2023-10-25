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
//    D.DWindow.enabled: true
    width: Applet.appletItems.lenght > 0 ? Applet.appletItems[0].width : 10
    height: Applet.appletItems.lenght > 0 ? Applet.appletItems[0].height : 10
//    DLayerShellWindow.anchors: DLayerShellWindow.AnchorTop
//    DLayerShellWindow.layer: DLayerShellWindow.LayerTop

    Control {
        id: content
        contentItem: Applet.appletItems[0]
    }
    Timer {
        running: true
        interval: 2000
        repeat: true
        onTriggered: {

                console.log("dddddddddddddddd", content.height, root.height)
        }
    }
}
