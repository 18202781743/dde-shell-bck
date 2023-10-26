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
    anchors.fill: parent
    height: view.height
    width: view.width

    function match(osdType)
    {
        syncModel()
        return osdType === "SwitchLayout"
    }

    ListView {
        id: view
        width: contentWidth
        height: contentHeight
        model: Applet.layouts

        delegate: RowLayout {
            height: 40

            Text {
                Layout.fillWidth: true
                Layout.leftMargin: 68
                Layout.topMargin: 13
                font: D.DTK.fontManager.t4
                Layout.alignment: Qt.AlignVCenter
                text: model.text
                color: Applet.currentLayout === model.key ? "blue" : "undefined"
            }
        }
    }
}
