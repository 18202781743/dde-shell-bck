// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "containment.h"
#include "applet_p.h"

#include "pluginloader.h"
#include "pluginmetadata.h"
#include "quick/appletitem.h"

#include <QLoggingCategory>


DS_BEGIN_NAMESPACE
DCORE_USE_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DContainmentPrivate : public DAppletPrivate
{
public:
    explicit DContainmentPrivate(DContainment *qq)
        : DAppletPrivate(qq)
    {

    }
    QList<DApplet *> m_applets;

    D_DECLARE_PUBLIC(DContainment)
};

DContainment::DContainment(QObject *parent)
    : DApplet(*new DContainmentPrivate(this))
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
    D_D(DContainment);
    Q_ASSERT(applet);
    d->m_applets.append(applet);
    Q_EMIT appletsChanged();
}

QList<DApplet *> DContainment::applets() const
{
    D_DC(DContainment);
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

QObject *DContainment::itemFor(DApplet *applet)
{
    return DAppletItem::itemForApplet(applet);
}

DS_END_NAMESPACE
