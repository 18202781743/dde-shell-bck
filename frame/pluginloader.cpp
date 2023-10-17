// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginloader.h"

#include "applet.h"
#include "containment.h"
#include "pluginmetadata.h"
#include "pluginfactory.h"

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QLoggingCategory>
#include <QPluginLoader>
#include <QStandardPaths>

DS_BEGIN_NAMESPACE;

static const QString MetaDataFileName{"metadata.json"};

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DPluginLoaderPrivate
{
public:
    DPluginLoaderPrivate(DPluginLoader *q)
        : q(q)
    {
        m_pluginDirs = buildinPackagePaths();
    }
    void init()
    {
        for (auto item : buildinPluginPaths()) {
            q->addPluginDir(item);
        }

        const QString rootDir(QCoreApplication::applicationDirPath());

        for (auto item : m_pluginDirs) {
            const QDirIterator::IteratorFlags flags = QDirIterator::Subdirectories;
            const QStringList nameFilters = {MetaDataFileName};

            QDirIterator it(item, nameFilters, QDir::Files, flags);
            QSet<QString> dirs;
            while (it.hasNext()) {
                it.next();

                const QString dir = it.fileInfo().absoluteDir().path();
                if (dirs.contains(dir)) {
                    continue;
                }
                dirs << dir;

                const QString metadataPath = it.fileInfo().absoluteFilePath();
                DPluginMetaData info = DPluginMetaData::fromJsonFile(metadataPath);
                if (!info.isValid())
                    continue;

                if (m_plugins.contains(info.pluginId()))
                    continue;

                m_plugins[info.pluginId()] = info;
            }
        }
    }

    QStringList buildinPackagePaths()
    {
        QStringList result;
        // 'DDE_SHELL_PACKAGE_PATH' directory.
        const auto dtkPluginPath = qgetenv("DDE_SHELL_PACKAGE_PATH");
        if (!dtkPluginPath.isEmpty())
            result.append(dtkPluginPath);

        result <<  QCoreApplication::applicationDirPath();
        result <<  QCoreApplication::applicationDirPath();
        result << QCoreApplication::applicationDirPath() + "/../packages";

        for (auto item : QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)) {
            result << item + "/dde-shell";
        }
        qCDebug(dsLog()) << "Buildin package paths" << result;

        return result;
    }

    QStringList buildinPluginPaths()
    {
        QStringList result;
        // 'DDE_SHELL_PACKAGE_PATH' directory.
        const auto dtkPluginPath = qgetenv("DDE_SHELL_PLUGIN_PATH");
        if (!dtkPluginPath.isEmpty())
            result.append(dtkPluginPath);

        result <<  QCoreApplication::applicationDirPath() + "/../plugins";
        result <<  DDE_SHELL_PLUGIN_INSTALL_DIR;

        qCDebug(dsLog()) << "Buildin plugin paths" << result;
        return result;
    }

    DAppletFactory *appletFactory(const DPluginMetaData &data)
    {
        DAppletFactory *factory = nullptr;
        const QString fileName = data.pluginId();
        QPluginLoader loader(fileName);
        loader.load();
        if (!loader.isLoaded()) {
            return factory;
        }

        const auto &meta = loader.metaData();

        do {
            const auto iid = meta["IID"].toString();
            if (iid.isEmpty())
                break;

            if (iid != QString(qobject_interface_iid<DAppletFactory *>()))
                break;

            if (!loader.instance()) {
                qWarning(dsLog) << "Load the plugin failed." << loader.errorString();
                break;
            }
            factory = qobject_cast<DAppletFactory *>(loader.instance());
            if (!factory) {
                qWarning(dsLog) << "The plugin isn't a DAppletFactory." << fileName;
                break;
            }
        } while (false);

        return factory;
    }

    DPluginMetaData pluginMetaData(const QString &pluginId) const
    {
        const auto it = m_plugins.constFind(pluginId);
        if (it == m_plugins.constEnd())
            return {};
        return it.value();
    }

    QStringList m_pluginDirs;
    QMap<QString, DPluginMetaData> m_plugins;
    DPluginLoader *q = nullptr;
};

DPluginLoader::DPluginLoader()
    : d(new DPluginLoaderPrivate(this))
{
}

DPluginLoader::~DPluginLoader()
{

}

DPluginLoader *DPluginLoader::instance()
{
    static DPluginLoader *g_instance = nullptr;
    if (!g_instance) {
        g_instance = new DPluginLoader();
        g_instance->d->init();
    }
    return g_instance;
}

QList<DPluginMetaData> DPluginLoader::plugins() const
{
    return d->m_plugins.values();
}

void DPluginLoader::addPackageDir(const QString &dir)
{
    d->m_pluginDirs.prepend(dir);
    d->init();
}

void DPluginLoader::addPluginDir(const QString &dir)
{
    QCoreApplication::addLibraryPath(dir);
}

DApplet *DPluginLoader::loadApplet(const QString &pluginId)
{
    DPluginMetaData metaData = d->pluginMetaData(pluginId);
    if (!metaData.isValid())
        return nullptr;

    DApplet *applet = nullptr;
    if (auto factory = d->appletFactory(metaData)) {
        qCDebug(dsLog()) << "Loading applet by factory" << pluginId;
        applet = factory->create();
    }
    if (!applet) {
        if (metaData.value("ContainmentType").isValid()) {
            applet = new DContainment();
        }
    }

    if (!applet) {
        applet = new DApplet();
    }
    if (applet) {
        applet->setMetaData(metaData);
    }
    return applet;
}

QList<DPluginMetaData> DPluginLoader::childrenPlugin(const QString &pluginId) const
{
    DPluginMetaData metaData = d->pluginMetaData(pluginId);
    if (!metaData.isValid())
        return {};

    const DPluginMetaData target(metaData);
    QList<DPluginMetaData> result;
    for (auto md : d->m_plugins.values()) {
        const QString parentId(md.value("Parent").toString());
        if (parentId == target.pluginId()) {
            result << md;
        }
    }
    return result;
}

DPluginMetaData DPluginLoader::parentPlugin(const QString &pluginId) const
{
    DPluginMetaData metaData = d->pluginMetaData(pluginId);
    if (!metaData.isValid())
        return {};

    const QString parentId(metaData.value("Parent").toString());
    return d->pluginMetaData(parentId);
}

DS_END_NAMESPACE
