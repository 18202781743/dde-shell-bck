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
    implicitHeight: view.contentHeight
    implicitWidth: view.contentWidth

    function match(osdType)
    {
        return Applet.state === 2 && osdType === "SwitchMonitors"
    }

    ListModel {
        id: displayModeModel
        ListElement {mode: 1; iconName: "osd_display_copy"; text: qsTr("Duplicate")}
        ListElement {mode: 2; iconName: "osd_display_expansion"; text: qsTr("Extend")}
        ListElement {mode: 3; iconName: "osd_display_custom1"; text: "placeholder"}
        ListElement {mode: 3; iconName: "osd_display_custom2"; text: "placeholder"}
    }

    ListView {
        id: view
        anchors.fill: parent
        model: displayModeModel

        delegate: RowLayout {
            width: 200
            height: 30
            visible: model.mode !== 3 || Applet.outputNames.length === 2

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
                text: model.mode === 3 ? qsTr("Only on %1").arg(Applet.outputNames[index - 2]) : model.text
            }
        }
    }
}
