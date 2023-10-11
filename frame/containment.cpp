// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "containment.h"

#include "pluginloader.h"
#include "pluginmetadata.h"

#include <QLoggingCategory>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DContainmentPrivate
{
public:
    QList<DApplet *> m_applets;
};

DContainment::DContainment(QObject *parent)
    : DApplet(parent)
    , d(new DContainmentPrivate())
{
}

DContainment::~DContainment()
{

}

DApplet *DContainment::createApplet(const QString &pluginId)
{
    auto applet = DPluginLoader::instance()->loadApplet(pluginId);
    if (applet) {
        addApplet(applet);
    }
    return applet;
}

void DContainment::addApplet(DApplet *applet)
{
    Q_ASSERT(applet);
    d->m_applets.append(applet);
    Q_EMIT appletsChanged();
}

QList<DApplet *> DContainment::applets() const
{
    return d->m_applets;
}

void DContainment::load()
{
    const auto children = DPluginLoader::instance()->childrenPlugin(pluginId());
    for (auto item : children) {
        const QString id = item.pluginId();
        auto applet = createApplet(id);

        if (auto containment = qobject_cast<DContainment *>(applet)) {
            containment->load();
        }
    }
}

DS_END_NAMESPACE
