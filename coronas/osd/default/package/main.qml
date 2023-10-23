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

    function match(osdType)
    {
        for (var i = 0; i < model.count; i++) {
            if (model.get(i).type === osdType) {
                iconName = model.get(i).iconName
                text = model.get(i).text
                console.log("*********", iconName, text)
                return true
            }
        }
        console.log("******", osdType)
        return false
    }

    property string iconName
    property string text
    ListModel {
        id: model
        ListElement {type: "WLANOn"; iconName: "osd_wifi_on"; text: qsTr("WLAN on")}
        ListElement {type: "WLANOff"; iconName: "osd_wifi_off"; text: qsTr("WLAN off")}
    }

    RowLayout {
        anchors.leftMargin: 68
        anchors.rightMargin: 26
        anchors.fill: parent

        D.DciIcon {
            sourceSize {
                width: 32
                height: 32
            }
            Layout.alignment: Qt.AlignLeft
            Layout.leftMargin: 14
            Layout.topMargin: 14
            visible: control.iconName
            name: control.iconName
        }
//        Control {
//            id: iconLabel
//            contentItem: D.DciIcon {
//                sourceSize {
//                    width: 32
//                    height: 32
//                }
//                Layout.alignment: Qt.AlignLeft
//                Layout.leftMargin: 14
//                Layout.topMargin: 14
//                visible: control.iconName
//                name: control.iconName
//                palette: D.DTK.makeIconPalette(iconLabel.palette)
//                mode: iconLabel.D.ColorSelector.controlState
//                theme: iconLabel.D.ColorSelector.controlTheme
//            }
//        }

        Text {
            Layout.fillWidth: true
            Layout.leftMargin: 68
            Layout.topMargin: 13
            font: D.DTK.fontManager.t4
            Layout.alignment: Qt.AlignVCenter
            visible: control.text
            text: control.text
        }
    }
}
