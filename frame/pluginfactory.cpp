// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginfactory.h"

#include <QMap>
#include <QLoggingCategory>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

static QMap<QString, DAppletFactory::CreateAppletFunction> g_appletFactory;

void DAppletFactory::registerInstance(CreateAppletFunction func)
{
    const QString key = metaObject()->className();
    g_appletFactory[key] = func;
}

DAppletFactory::DAppletFactory()
    : QObject()
{

}

DApplet *DAppletFactory::create(QObject *parent)
{
    const QString key = metaObject()->className();
    if (g_appletFactory.contains(key)) {
        DAppletFactory::CreateAppletFunction func = g_appletFactory.value(key);
        return func(parent);
    }
    return nullptr;
}

DS_END_NAMESPACE
