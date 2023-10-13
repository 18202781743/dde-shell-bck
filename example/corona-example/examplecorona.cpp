// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "examplecorona.h"

#include "pluginfactory.h"


ExampleCorona::ExampleCorona(QObject *parent)
    : DContainment(parent)
    , m_corona(new DCorona)
{
}

ExampleCorona::~ExampleCorona()
{

}

void ExampleCorona::load()
{
    DContainment::load();
}

void ExampleCorona::init()
{
    const QString pluginId = pluginMetaData().pluginId();
    m_corona->setRootPlugin(pluginId);
    m_corona->load();
}

D_APPLET_CLASS(ExampleCorona)

#include "examplecorona.moc"
