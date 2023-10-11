// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "appletitem.h"
#include "containment.h"

#include <QStringList>

DS_BEGIN_NAMESPACE

class DContainmentItemPrivate;
/**
 * @brief UI插件实例项
 */
class Q_DECL_EXPORT DContainmentItem : public DAppletItem
{
    Q_OBJECT
public:
    DContainmentItem(QQuickItem *parent = nullptr);
    virtual ~DContainmentItem();


    static DContainment *qmlAttachedProperties(QObject *object);

public Q_SLOTS:
    QObject *itemFor(DApplet *applet);

private:
    DContainmentItemPrivate *d = nullptr;
};

DS_END_NAMESPACE

QML_DECLARE_TYPEINFO(DS_NAMESPACE::DContainmentItem, QML_HAS_ATTACHED_PROPERTIES)
