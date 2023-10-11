// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "examplecorona.h"

#include "appletitem.h"
#include "pluginfactory.h"

ExampleCorona::ExampleCorona(QObject *parent)
    : DContainment(parent)
    , m_view(new DPanelView)
    , m_corona(new DCorona)
{
    m_view->resize(600, 400);
}

ExampleCorona::~ExampleCorona()
{

}

void ExampleCorona::load()
{
    const QString pluginId = pluginMetaData().pluginId();
    auto containment = m_corona->createContainment(pluginId);
    if (!containment) {
        qWarning() << "Load error:" << pluginId;
        return;
    }

    auto appletItem = DAppletItem::itemForApplet(containment);
    appletItem->setSize(m_view->size());
    appletItem->setParentItem(m_view->contentItem());
}

void ExampleCorona::init()
{
    load();
    m_view->show();
}

DPanelView *ExampleCorona::view()
{
    return m_view;
}

D_APPLET_CLASS(ExampleCorona)

#include "examplecorona.moc"
