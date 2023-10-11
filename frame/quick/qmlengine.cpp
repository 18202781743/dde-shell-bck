// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "qmlengine.h"
#include "applet.h"

#include <QLoggingCategory>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QTimer>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DQmlEnginePrivate
{
public:
    DApplet *m_applet = nullptr;
    QQmlContext *m_context = nullptr;
    QQmlComponent *m_component = nullptr;
    QObject *m_rootObject = nullptr;
    QQmlEngine *engine()
    {
        static QQmlEngine *s_engine = nullptr;
        if (!s_engine) {
            s_engine = new QQmlEngine();
        }
        return s_engine;
    }
};

DQmlEngine::DQmlEngine(DApplet *applet, QObject *parent)
    : QObject(parent)
    , d(new DQmlEnginePrivate())
{
    d->m_applet = applet;
}

DQmlEngine::~DQmlEngine()
{
}

QObject *DQmlEngine::beginCreate()
{
    auto component = new QQmlComponent(engine(), this);
    component->loadUrl(d->m_applet->url());
    if (component->isError()) {
        return nullptr;
    }
    d->m_component = component;
    auto context = new QQmlContext(engine());
    auto object = component->beginCreate(context);
    return object;
}

void DQmlEngine::completeCreate()
{
    if (!d->m_component)
        return;

    d->m_component->completeCreate();
}

QObject *DQmlEngine::create()
{
    auto object = beginCreate();
    if (object) {
        QTimer::singleShot(10, this , [this](){
            completeCreate();
        });
    }
    return object;
}

QQmlEngine *DQmlEngine::engine()
{
    return d->engine();
}

DS_END_NAMESPACE
