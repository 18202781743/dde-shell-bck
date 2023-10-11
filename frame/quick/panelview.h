// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"

#include <QQuickWindow>

DS_BEGIN_NAMESPACE

class DPluginMetaData;
/**
 * @brief 插件项
 */
class DPanelViewPrivate;
class Q_DECL_EXPORT DPanelView : public QQuickWindow
{
    Q_OBJECT
public:
    DPanelView(QWindow *parent = nullptr);
    virtual ~DPanelView();

private:
    DPanelViewPrivate *d = nullptr;
};

DS_END_NAMESPACE