// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

import org.deepin.ds 1.0
import org.deepin.dtk 1.0 as D

Window {
    id: root
    visible: Applet.visible
    D.DWindow.enabled: true

    width: osdView ? osdView.width : 100
    height: osdView ? osdView.height : 100

    property Item osdView

    Repeater {
        model: Applet.appletItems
        delegate: Control {
            visible: modelData.update(Applet.osdType)
            contentItem: modelData
            padding: 20
            onVisibleChanged: {
                if (visible) {
                    root.osdView = this
                }
            }
            background: D.FloatingPanel {
            }
        }
    }
}
