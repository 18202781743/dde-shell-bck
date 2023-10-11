// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "applet.h"

#include <QStringList>
#include <QVariant>

DS_BEGIN_NAMESPACE

class DPluginMetaData;
/**
 * @brief 插件项
 */
class DContainmentPrivate;
class Q_DECL_EXPORT DContainment : public DApplet
{
    Q_OBJECT
    Q_PROPERTY(QList<DApplet *> applets READ applets NOTIFY appletsChanged)
public:
    DContainment(QObject *parent = nullptr);
    virtual ~DContainment();

    DApplet *createApplet(const QString &pluginId);
    void addApplet(DApplet *applet);
    QList<DApplet *> applets() const;

    void load();

Q_SIGNALS:
    void appletsChanged();

private:
    DContainmentPrivate *d = nullptr;
};

DS_END_NAMESPACE