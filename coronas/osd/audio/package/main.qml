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
        return types.indexOf(osdType) >= 0
    }

    property var types: ["AudioUp",
        "AudioDown",
        "AudioMute",
        "AudioUpAsh",
        "AudioDownAsh",
        "AudioMuteAsh"
    ]

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
            name: Applet.iconName
        }

        D.ProgressBar {
            Layout.preferredWidth: 200
            Layout.topMargin: 13
            Layout.alignment: Qt.AlignVCenter
            from: 0
            value: Applet.volumeValue / (Applet.increaseVolume ? 1.5 : 1.0)
            to: 1
        }

        Text {
            Layout.topMargin: 13
            font: D.DTK.fontManager.t4
            Layout.alignment: Qt.AlignVCenter
            text: Applet.volumeValue * 100
        }
    }
}
