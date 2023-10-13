// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "corona.h"
#include "dstypes.h"
#include "pluginloader.h"
#include "quick/panelview.h"
#include "quick/qmlengine.h"

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

class DCoronaPrivate
{
public:
    DApplet *m_applet = nullptr;
    QString m_pluginId;
    QQuickWindow *m_window = nullptr;
};

DCorona::DCorona(QObject *parent)
    : QObject(parent)
    , d(new DCoronaPrivate())
{
}

DCorona::~DCorona()
{

}

void DCorona::setRootPlugin(const QString &pluginId)
{
    d->m_pluginId = pluginId;
}

void DCorona::createWindow()
{
    if (!d->m_applet)
        return;

    DQmlEngine *engine = new DQmlEngine(d->m_applet);

    auto rootObject = engine->create();

    auto window = qobject_cast<QQuickWindow *>(rootObject);
    if (window) {
        d->m_window = window;
        d->m_window->setProperty("_ds_window_applet", QVariant::fromValue(d->m_applet));

        engine->completeCreate();

        if (auto panel = qobject_cast<DPanelView *>(qmlAttachedPropertiesObject<DPanelView>(window))) {
            const QString position = d->m_applet->pluginMetaData().value("Position").toString();
            panel->setPosition(typePosition(position));
        }
    }
}

QQuickWindow *DCorona::window() const
{
    return d->m_window;
}

void DCorona::load()
{
    auto applet = DPluginLoader::instance()->loadApplet(d->m_pluginId);
    if (applet) {
        d->m_applet = applet;

        d->m_applet->load();
    }

    createWindow();

    if (window()) {
        window()->show();
    }
}

void DCorona::save()
{

}

DS_END_NAMESPACE
