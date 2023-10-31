// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import org.deepin.ds 1.0
import org.deepin.dtk 1.0 as D

AppletItem {
    id: control
    implicitWidth: childrenRect.width
    implicitHeight: childrenRect.height

    function update(osdType)
    {
        if (match(osdType)) {
            Applet.sync()
            return true
        }
        return false
    }
    function match(osdType)
    {
        return osdType === "SwitchMonitors"
    }
    ListView {
        id: view
        width: 300
        height: contentHeight
        model: Applet.planItems

        delegate: RowLayout {
            height: 40

            D.DciIcon {
                sourceSize {
                    width: 32
                    height: 32
                }
                Layout.alignment: Qt.AlignLeft
                Layout.leftMargin: 14
                Layout.topMargin: 14
                name: model.iconName
            }

            Text {
                Layout.fillWidth: true
                Layout.leftMargin: 68
                Layout.topMargin: 13
                font: D.DTK.fontManager.t4
                Layout.alignment: Qt.AlignVCenter
                text: model.text
                color: Applet.currentPlanItem.key === model.key ? "blue" : "undefined"
            }
        }
    }
}
