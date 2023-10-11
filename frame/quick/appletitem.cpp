// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "appletitem.h"
#include "qmlengine.h"

#include <QLoggingCategory>
#include <QQmlEngine>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

static void registType()
{
    const char *uri = "org.deepin.ds";
    qmlRegisterAnonymousType<DApplet>(uri, 1);
    qmlRegisterType<DAppletItem>(uri, 1, 0, "AppletItem");

    qmlRegisterUncreatableType<DAppletItem>(uri, 1, 0, "Applet", "Applet Attached");
}

Q_CONSTRUCTOR_FUNCTION(registType);

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
    return nullptr;
}

DS_END_NAMESPACE
