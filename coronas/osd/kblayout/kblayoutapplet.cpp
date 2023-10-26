// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "kblayoutapplet.h"

#include "pluginfactory.h"

#include <QDBusConnection>
#include <QDBusPendingCall>
#include <QDBusReply>

#include <DDBusSender>

DS_BEGIN_NAMESPACE

static DDBusSender keyboardInter()
{
    return DDBusSender().service("org.deepin.dde.InputDevices1")
        .path("/org/deepin/dde/InputDevice1/Keyboard")
        .interface("org.deepin.dde.InputDevice1.Keyboard");
}

KBLayout::KBLayout(const QString &key, const QString &text, QObject *parent)
    : QObject(parent)
    , m_key(key)
    , m_text(text)
{

}

QString KBLayout::text() const
{
    return m_text;
}

QString KBLayout::key() const
{
    return m_key;
}

QString KBLayoutApplet::currentLayout() const
{
    return m_currentLayout;
}

void KBLayoutApplet::setCurrentLayout(const QString &newCurrentLayout)
{
    if (m_currentLayout == newCurrentLayout)
        return;
    m_currentLayout = newCurrentLayout;
    emit currentLayoutChanged();
}

void KBLayoutApplet::fetchLayouts()
{
    auto inter = keyboardInter();
    QDBusReply<QVariant> userLayoutList = inter.property("UserLayoutList").get();
    if (!userLayoutList.isValid()) {
        qWarning() << "Failed to fetch UserLayoutList" << userLayoutList.error();
        return;
    }
    auto userLayouts = qdbus_cast<QStringList>(userLayoutList.value());
    userLayouts.removeDuplicates();

    QDBusReply<QDBusArgument> layoutList(inter.method("LayoutList").call());

    if (!layoutList.isValid()) {
        qWarning() << "Failed to fetch LayoutList" << layoutList.error();
        return;
    }
    const auto layouts = qdbus_cast<QMap<QString, QString>>(layoutList.value());

    for (auto item : userLayouts) {
        const auto text = layouts.value(item, item);
        auto layoutItem = new KBLayout(item, text, this);
        m_layouts.append(layoutItem);
    }
    Q_EMIT layoutsChanged();
}

void KBLayoutApplet::fetchCurrentLayout()
{
    QDBusReply<QVariant> currentLayoutList = keyboardInter().property("CurrentLayout").get();
    if (!currentLayoutList.isValid()) {
        qWarning() << "Failed to fetch CurrentLayout" << currentLayoutList.error();
        return;
    }
    setCurrentLayout(qdbus_cast<QString>(currentLayoutList));
}

KBLayoutApplet::KBLayoutApplet(QObject *parent)
    : DApplet(parent)
{
}

void KBLayoutApplet::init()
{
    fetchLayouts();
    fetchCurrentLayout();
}

QQmlListProperty<KBLayout> KBLayoutApplet::layouts()
{
    return QQmlListProperty<KBLayout>(this, &m_layouts);
}

D_APPLET_CLASS(KBLayoutApplet)

DS_END_NAMESPACE

#include "kblayoutapplet.moc"
