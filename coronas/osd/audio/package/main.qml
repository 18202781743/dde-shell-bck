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
    property string iconName: {
        if (Applet.mute)
            return "osd_volume_mute"
        var iconPrefix = "osd_volume_"
        if (Applet.volume <= 0.33)
            return iconPrefix + "33"
        else if (Applet.volume <= 0.66)
            return iconPrefix + "66"
        else if (Applet.volume <= 1)
            return iconPrefix + "100"
        else if (Applet.volume > 1)
            return iconPrefix + "more"

        return ""
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

        D.ProgressBar {
            Layout.fillWidth: true
            Layout.leftMargin: 68
            Layout.topMargin: 13
            Layout.alignment: Qt.AlignVCenter
            from: 0
            to: Applet.increaseVolume / Applet.volumeValue
        }
    }
}
