// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "containment.h"

#include <QStringList>
#include <QVariant>

DS_BEGIN_NAMESPACE

/**
 * @brief 插件集
 * 序列化和反序列化插件
 */
class DCoronaPrivate;
class Q_DECL_EXPORT DCorona : public QObject
{
    Q_OBJECT
public:
    explicit DCorona(QObject *parent = nullptr);
    virtual ~DCorona();

    QList<DContainment *> containments() const;

    DContainment *createContainment(const QString &pluginId, const QVariantList &args = QVariantList());

    // 从配置文件中加载插件
    virtual void load();
    // 保存插件状态
    virtual void save();

private:
    DCoronaPrivate *d = nullptr;
};

DS_END_NAMESPACE
