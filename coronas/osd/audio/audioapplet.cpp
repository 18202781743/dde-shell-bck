// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "audioapplet.h"

#include "pluginfactory.h"

#include <QDBusConnection>

DS_BEGIN_NAMESPACE

double AudioApplet::volume() const
{
    return m_volume;
}

void AudioApplet::setVolume(double newVolume)
{
    if (qFuzzyCompare(m_volume, newVolume))
        return;
    m_volume = newVolume;
    emit volumeChanged();
}

bool AudioApplet::mute() const
{
    return m_mute;
}

void AudioApplet::setMute(bool newMute)
{
    if (m_mute == newMute)
        return;
    m_mute = newMute;
    emit muteChanged();
}

AudioApplet::AudioApplet(QObject *parent)
    : DApplet(parent)
{

}

void AudioApplet::init()
{
}

double AudioApplet::volumeValue() const
{
    return m_volumeValue;
}

void AudioApplet::setVolumeValue(double newVolumeValue)
{
    if (qFuzzyCompare(m_volumeValue, newVolumeValue))
        return;
    m_volumeValue = newVolumeValue;
    emit volumeValueChanged();
}

double AudioApplet::increaseVolume() const
{
    return m_increaseVolume;
}

void AudioApplet::setIncreaseVolume(double newIncreaseVolume)
{
    if (qFuzzyCompare(m_increaseVolume, newIncreaseVolume))
        return;
    m_increaseVolume = newIncreaseVolume;
    emit increaseVolumeChanged();
}

D_APPLET_CLASS(AudioApplet)

DS_END_NAMESPACE

#include "audioapplet.moc"
