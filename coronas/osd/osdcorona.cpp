// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "osdcorona.h"

#include "pluginfactory.h"

#include <QDBusConnection>
#include <QTimer>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(osdLog, "dde.shell.osd")

DS_BEGIN_NAMESPACE

QString OsdCorona::osdType() const
{
    return m_osdType;
}

bool OsdCorona::visible() const
{
    return m_visible;
}

void OsdCorona::showText(const QString &text)
{
    qCInfo(osdLog()) << "show text" << text;
    setOsdType(text);
    showOsd();
}

void OsdCorona::hideOsd()
{
    m_osdTimer->stop();
    setVisible(false);
}

void OsdCorona::showOsd()
{
    m_osdTimer->stop();

    m_osdTimer->start();
    setVisible(true);
}

void OsdCorona::setVisible(const bool visible)
{
    if (visible == m_visible)
        return;
    m_visible = visible;
    Q_EMIT visibleChanged();
}

OsdCorona::OsdCorona(QObject *parent)
    : DCorona(parent)
{
}

void OsdCorona::init()
{
    auto bus = QDBusConnection::sessionBus();
    bus.registerObject(QStringLiteral("/org/deepin/osdService"),
                                                 this,
                                                 QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);

    m_osdTimer = new QTimer(this);
    m_osdTimer->setInterval(3000);
    m_osdTimer->setSingleShot(true);
    QObject::connect(m_osdTimer, &QTimer::timeout, this, &OsdCorona::hideOsd);
    DCorona::init();
}

void OsdCorona::setOsdType(const QString &osdType)
{
//    if (m_osdType == osdType)
//        return;
    m_osdType = osdType;
    emit osdTypeChanged(m_osdType);
}

D_APPLET_CLASS(OsdCorona)

DS_END_NAMESPACE

#include "osdcorona.moc"
