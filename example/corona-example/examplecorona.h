// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "corona.h"

DS_USE_NAMESPACE

class Q_DECL_EXPORT ExampleCorona : public DContainment
{
    Q_OBJECT
public:
    explicit ExampleCorona(QObject *parent = nullptr);

    virtual ~ExampleCorona();

    void load() override;

    virtual void init() override;

private:
    DCorona *m_corona;

};
