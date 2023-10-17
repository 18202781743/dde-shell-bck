// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "applet.h"

#include <DObject>
#include <QVariant>

DS_BEGIN_NAMESPACE

/**
 * @brief 容器插件
 */
class DContainmentPrivate;
class Q_DECL_EXPORT DContainment : public DApplet
{
    Q_OBJECT
    Q_PROPERTY(QList<DApplet *> applets READ applets NOTIFY appletsChanged)
    D_DECLARE_PRIVATE(DContainment)
public:
    DContainment(QObject *parent = nullptr);
    virtual ~DContainment();

    DApplet *createApplet(const QString &pluginId);
    void addApplet(DApplet *applet);
    QList<DApplet *> applets() const;

    void load() override;

public Q_SLOTS:
    QObject *itemFor(DApplet *applet);

Q_SIGNALS:
    void appletsChanged();
};

DS_END_NAMESPACE
