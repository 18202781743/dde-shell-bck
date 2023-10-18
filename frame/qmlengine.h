// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"

#include <QQmlEngine>

DS_BEGIN_NAMESPACE

class DApplet;
class DQmlEnginePrivate;
/**
 * @brief UI插件实例项
 */
class Q_DECL_EXPORT DQmlEngine : public QObject
{
    Q_OBJECT
public:
    DQmlEngine(DApplet *applet, QObject *parent = nullptr);
    DQmlEngine(QObject *parent = nullptr);
    virtual ~DQmlEngine();

    QObject *beginCreate();
    void completeCreate();

    QObject *create();
    QQmlEngine *engine();

private:
    DQmlEnginePrivate *d = nullptr;
};

DS_END_NAMESPACE