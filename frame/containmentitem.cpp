// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "containmentitem.h"

#include <QLoggingCategory>
#include <QQmlEngine>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

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
