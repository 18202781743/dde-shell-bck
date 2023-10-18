// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "qmlengine.h"
#include "applet.h"

#include <QCoreApplication>
#include <QDir>
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
            const QString rootDir = QCoreApplication::applicationDirPath();
            s_engine->addImportPath(rootDir + "/../plugins");
            s_engine->addImportPath(DDE_SHELL_QML_INSTALL_DIR);
            qCDebug(dsLog()) << "Engine importPaths" << s_engine->importPathList();
        }
        return s_engine;
    }
    QString appletUrl() const
    {
        auto url = m_applet->pluginMetaData().value("Url").toString();
        if (url.isEmpty())
            return QString();

        return QDir(m_applet->pluginMetaData().pluginDir()).absoluteFilePath(url);
    }
};

DQmlEngine::DQmlEngine(DApplet *applet, QObject *parent)
    : QObject(parent)
    , d(new DQmlEnginePrivate())
{
    d->m_applet = applet;
}

DQmlEngine::DQmlEngine(QObject *parent)
    : QObject(parent)
    , d(new DQmlEnginePrivate())
{

}

DQmlEngine::~DQmlEngine()
{
}

QObject *DQmlEngine::beginCreate()
{
    auto component = new QQmlComponent(engine(), this);
    const QString url = d->appletUrl();
    component->loadUrl(url);
    if (component->isError()) {
        qCWarning(dsLog()) << "Loading url failed" << component->errorString();
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

    if (!d->m_component->isReady())
        return;

    d->m_component->completeCreate();
}

QObject *DQmlEngine::create()
{
    auto object = beginCreate();
    if (object) {
        QTimer::singleShot(0, this , [this](){
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
