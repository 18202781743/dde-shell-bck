// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "pluginmetadata.h"

#include <QStringList>
#include <QVariant>

DS_BEGIN_NAMESPACE

class DPluginMetaData;
/**
 * @brief 插件项，单个插件实例
 */
class DAppletPrivate;
class Q_DECL_EXPORT DApplet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pluginId READ pluginId CONSTANT FINAL)
public:
    DApplet(QObject *parent = nullptr);
    virtual ~DApplet();

    void setMetaData(const DPluginMetaData &metaData);
    QString pluginId() const;

    QString url() const;

    DPluginMetaData pluginMetaData() const;

    virtual void init();

private:
    DAppletPrivate *d = nullptr;
};

DS_END_NAMESPACE