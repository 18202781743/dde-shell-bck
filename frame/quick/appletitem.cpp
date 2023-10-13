// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "appletitem.h"
#include "qmlengine.h"

#include <QLoggingCategory>
#include <QQmlEngine>
#include <QQuickWindow>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DAppletItemPrivate
{
public:

    DApplet *m_applet = nullptr;
    DQmlEngine *m_engine = nullptr;
};

DAppletItem::DAppletItem(QQuickItem *parent)
    : QQuickItem(parent)
    , d(new DAppletItemPrivate())
{
}

DAppletItem::~DAppletItem()
{
}

DApplet *DAppletItem::applet() const
{
    return d->m_applet;
}

DAppletItem *DAppletItem::itemForApplet(DApplet *applet)
{
    DQmlEngine *engine = new DQmlEngine(applet);

    auto rootObject = engine->create();

    auto item = qobject_cast<DAppletItem *>(rootObject);
    if (!item)
        return nullptr;

    item->d->m_applet = applet;

    return item;
}

DApplet *DAppletItem::qmlAttachedProperties(QObject *object)
{
    QQuickItem *item = qobject_cast<QQuickItem *>(object);
    while (item) {
        if (auto appletItem = qobject_cast<DAppletItem *>(item)) {
            return appletItem->applet();
        }
        item = item->parentItem();
    }
    if (!item) {
        item = qobject_cast<QQuickItem *>(object);
        if(auto applet = item->window()->property("_ds_window_applet").value<DApplet *>()) {
            return applet;
        }
    }
    return nullptr;
}

DS_END_NAMESPACE
