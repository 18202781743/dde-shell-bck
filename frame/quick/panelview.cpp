// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "panelview.h"

#include <QLoggingCategory>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DPanelViewPrivate
{
public:
    DPanelViewPrivate()
    {

    }
};

DPanelView::DPanelView(QWindow *parent)
    : QQuickWindow(parent)
    , d(new DPanelViewPrivate())
{
}

DPanelView::~DPanelView()
{

}

DS_END_NAMESPACE
