// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import org.deepin.ds 1.0

ContainmentItem {
    id: root
    Control {
        anchors.fill: parent
        contentItem: Loader {
            id: appletLoader
            active: applet
            property AppletItem applet
            width: applet ? applet.width : 30
            height: applet ? applet.height : 30

            Component.onCompleted: {
                if (Applet.applets.length <= 0)
                    return
                var applet = Applet.applets[0]
                var appletItem = root.itemFor(applet)
                appletLoader.applet = appletItem
                appletItem.parent = appletLoader
                appletItem.anchors.fill = appletLoader
            }
        }
        background: Rectangle {
            color: "plum"
            opacity: 0.8
        }
    }
}