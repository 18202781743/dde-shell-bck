// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "corona.h"
#include "private/corona_p.h"

#include "dstypes.h"
#include "pluginloader.h"
#include "panelview.h"
#include "qmlengine.h"

#include <QLoggingCategory>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

static Types::Position typePosition(const QString &p)
{
    const QMap<QString, Types::Position> mapping {
        {"left", Types::LeftPositioned},
        {"right", Types::RightPositioned},
        {"center", Types::CenterPositioned},
        {"top", Types::TopPositioned},
        {"bottom", Types::BottomPositioned}
    };
    if (mapping.contains(p)) {
        return mapping.value(p);
    }
    return {};
}

DCorona::DCorona(QObject *parent)
    : DContainment(*new DCoronaPrivate(this), parent)
{
}

DCorona::~DCorona()
{

}

void DCoronaPrivate::createWindow()
{
    D_Q(DCorona);
}

QQuickWindow *DCorona::window() const
{
    D_DC(DCorona);
    return d->m_window;
}

void DCorona::load()
{
    D_D(DCorona);
    DContainment::load();
}

void DCorona::init()
{
    D_D(DCorona);

    auto applet = this;

    DQmlEngine *engine = new DQmlEngine(applet, applet);

    auto rootObject = engine->beginCreate();

    auto window = qobject_cast<QQuickWindow *>(rootObject);
    if (window) {
        d->m_window = window;
        d->m_window->setProperty("_ds_window_applet", QVariant::fromValue(applet));

        if (auto panel = qobject_cast<DPanelView *>(qmlAttachedPropertiesObject<DPanelView>(window))) {
            const QString position = applet->pluginMetaData().value("Position").toString();
            panel->setPosition(typePosition(position));
        }
    }

    DContainment::init();

    engine->completeCreate();
}

DS_END_NAMESPACE
