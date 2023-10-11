// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "pluginmetadata.h"
#include <QObject>

DS_BEGIN_NAMESPACE

class DApplet;

/**
 * @brief 插件加载，创建
 */
class DPluginLoaderPrivate;
class Q_DECL_EXPORT DPluginLoader : public QObject
{
    Q_OBJECT
public:
    DPluginLoader();
    virtual ~DPluginLoader();

    static DPluginLoader *instance();
    QList<DPluginMetaData> plugins() const;
    void addPackageDir(const QString &dir);
    void addPluginDir(const QString &dir);

    DApplet *loadApplet(const QString &pluginId);

    QList<DPluginMetaData> childrenPlugin(const QString &pluginId) const;
    DPluginMetaData parentPlugin(const QString &pluginId) const;
private:
    QScopedPointer<DPluginLoaderPrivate> d;
};

DS_END_NAMESPACE
