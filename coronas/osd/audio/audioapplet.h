// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "applet.h"

DS_BEGIN_NAMESPACE

class Q_DECL_EXPORT AudioApplet : public DApplet
{
    Q_OBJECT
    Q_PROPERTY(bool mute READ mute NOTIFY muteChanged FINAL)
    Q_PROPERTY(double volume READ volume NOTIFY volumeChanged FINAL)
    Q_PROPERTY(double increaseVolume READ increaseVolume NOTIFY increaseVolumeChanged FINAL)
    Q_PROPERTY(double volumeValue READ volumeValue NOTIFY volumeValueChanged FINAL)
public:
    explicit AudioApplet(QObject *parent = nullptr);
    virtual void init() override;

    double increaseVolume() const;
    void setIncreaseVolume(double newIncreaseVolume);

    double volumeValue() const;
    void setVolumeValue(double newVolumeValue);

    bool mute() const;
    void setMute(bool newMute);

    double volume() const;
    void setVolume(double newVolume);

Q_SIGNALS:

    void increaseVolumeChanged();

    void volumeValueChanged();

    void muteChanged();

    void volumeChanged();

private:
    double m_increaseVolume = 1.0;
    double m_volumeValue = 1.0;
    bool m_mute;
    double m_volume;
};

DS_END_NAMESPACE
