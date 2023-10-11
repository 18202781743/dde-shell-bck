// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import org.deepin.ds 1.0

ContainmentItem {
    id: root
    width: 200
    height: 200
    RowLayout {

        Repeater {
            model: Applet.applets
            delegate: Loader {
                id: appletLoader
                property var applet
                width: applet ? applet.width : 30
                height: applet ? applet.height : 30

                Component.onCompleted: {
                    var applet = modelData
                    var appletItem = root.itemFor(applet)
                    appletLoader.applet = appletItem
                    appletItem.parent = appletLoader
                    appletItem.anchors.fill = appletLoader
                }

            }
        }

    }

}