// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "containmentitem.h"

#include <QLoggingCategory>
#include <QQmlEngine>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

static void registType()
{
    const char *uri = "org.deepin.ds";
    qmlRegisterType<DContainmentItem>(uri, 1, 0, "ContainmentItem");
    qmlRegisterUncreatableType<DContainmentItem>(uri, 1, 0, "Containment", "Containment Attached");
}

Q_CONSTRUCTOR_FUNCTION(registType);

class DContainmentItemPrivate
{
public:

};

DContainmentItem::DContainmentItem(QQuickItem *parent)
    : DAppletItem(parent)
    , d(new DContainmentItemPrivate())
{
}

DContainmentItem::~DContainmentItem()
{
}

DContainment *DContainmentItem::qmlAttachedProperties(QObject *object)
{
    return qobject_cast<DContainment *>(DAppletItem::qmlAttachedProperties(object));
}

QObject *DContainmentItem::itemFor(DApplet *applet)
{
    DAppletItem *item = itemForApplet(applet);

    return item;
}

DS_END_NAMESPACE
