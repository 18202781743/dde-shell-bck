// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "applet.h"

#include "pluginmetadata.h"

#include <QDir>
#include <QLoggingCategory>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DAppletPrivate
{
public:
    DPluginMetaData m_metaData;
};

DApplet::DApplet(QObject *parent)
    : QObject(parent)
    , d(new DAppletPrivate())
{
}

DApplet::~DApplet()
{

}

void DApplet::setMetaData(const DPluginMetaData &metaData)
{
    d->m_metaData = metaData;
}

QString DApplet::pluginId() const
{
    return d->m_metaData.pluginId();
}

QString DApplet::url() const
{
    auto url = d->m_metaData.value("Url").toString();
    if (url.isEmpty())
        return QString();

    return QDir(d->m_metaData.pluginDir()).absoluteFilePath(url);
}

DPluginMetaData DApplet::pluginMetaData() const
{
    return d->m_metaData;
}

void DApplet::init()
{

}

DS_END_NAMESPACE
