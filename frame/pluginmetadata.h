// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include <QSharedData>
#include <QVariant>

DS_BEGIN_NAMESPACE

/**
 * @brief 插件元数据
 */
class DPluginMetaDataPrivate;
class Q_DECL_EXPORT DPluginMetaData : public QObject
{
    Q_OBJECT
public:
    DPluginMetaData();
    DPluginMetaData(const DPluginMetaData &other);
    DPluginMetaData &operator=(const DPluginMetaData &other);
    bool operator==(const DPluginMetaData  &other) const;
    virtual ~DPluginMetaData();
    bool isValid() const;
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant());

    QString pluginId() const;
    QString pluginDir() const;

    static DPluginMetaData fromJsonFile(const QString &file);

private:
    QExplicitlySharedDataPointer<DPluginMetaDataPrivate> d;
};

DS_END_NAMESPACE