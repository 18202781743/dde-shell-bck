// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "corona.h"
#include "pluginloader.h"

#include <QLoggingCategory>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DCoronaPrivate
{
public:
    QList<DContainment *> m_containments;
};

DCorona::DCorona(QObject *parent)
    : QObject(parent)
    , d(new DCoronaPrivate())
{
}

DCorona::~DCorona()
{

}

QList<DContainment *> DCorona::containments() const
{
    return d->m_containments;
}

DContainment *DCorona::createContainment(const QString &pluginId, const QVariantList &args)
{
    auto applet = DPluginLoader::instance()->loadApplet(pluginId);

    auto containment = qobject_cast<DContainment *>(applet);
    if (!containment)
        return nullptr;
    containment->load();
    d->m_containments.append(containment);
    return containment;
}

void DCorona::load()
{
    // 创建 containments

}

void DCorona::save()
{

}

DS_END_NAMESPACE
