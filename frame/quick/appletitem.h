// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "applet.h"

#include <QStringList>
#include <QQuickItem>

DS_BEGIN_NAMESPACE

class DAppletItemPrivate;
/**
 * @brief UI插件实例项
 */
class Q_DECL_EXPORT DAppletItem : public QQuickItem
{
    Q_OBJECT
public:
    DAppletItem(QQuickItem *parent = nullptr);
    virtual ~DAppletItem();

    DApplet *applet() const;

    static DAppletItem *itemForApplet(DApplet *applet);

    static DApplet *qmlAttachedProperties(QObject *object);

private:
    DAppletItemPrivate *d = nullptr;
};

DS_END_NAMESPACE

QML_DECLARE_TYPEINFO(DS_NAMESPACE::DAppletItem, QML_HAS_ATTACHED_PROPERTIES)
