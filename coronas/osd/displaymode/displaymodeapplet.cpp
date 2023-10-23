// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "displaymodeapplet.h"

#include "pluginfactory.h"

#include <QDBusConnection>

DS_BEGIN_NAMESPACE

QStringList DisPlayModeApplet::outputNames() const
{
    return m_outputNames;
}

void DisPlayModeApplet::setOutputNames(const QStringList &newOutputNames)
{
    if (m_outputNames == newOutputNames)
        return;
    m_outputNames = newOutputNames;
    emit outputNamesChanged();
}

QString DisPlayModeApplet::primaryScreen() const
{
    return m_primaryScreen;
}

void DisPlayModeApplet::setPrimaryScreen(const QString &newPrimaryScreen)
{
    if (m_primaryScreen == newPrimaryScreen)
        return;
    m_primaryScreen = newPrimaryScreen;
    emit primaryScreenChanged();
}

int DisPlayModeApplet::displayMode() const
{
    return m_displayMode;
}

void DisPlayModeApplet::setDisplayMode(int newDisplayMode)
{
    if (m_displayMode == newDisplayMode)
        return;
    m_displayMode = newDisplayMode;
    emit displayModeChanged();
}

int DisPlayModeApplet::state() const
{
    return m_state;
}

void DisPlayModeApplet::setState(int newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}

DisPlayModeApplet::DisPlayModeApplet(QObject *parent)
    : DApplet(parent)
{

}

void DisPlayModeApplet::init()
{
}

D_APPLET_CLASS(DisPlayModeApplet)

DS_END_NAMESPACE

#include "displaymodeapplet.moc"
