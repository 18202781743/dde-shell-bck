// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "corona.h"
#include "panelview.h"

DS_USE_NAMESPACE

class Q_DECL_EXPORT ExampleCorona : public DContainment
{
    Q_OBJECT
public:
    explicit ExampleCorona(QObject *parent = nullptr);

    virtual ~ExampleCorona();

    void load();

    virtual void init() override;

    DPanelView *view();

private:
    DPanelView *m_view;
    DCorona *m_corona;

};
