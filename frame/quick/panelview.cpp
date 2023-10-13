// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "panelview.h"

#include <QScreen>
#include <QLoggingCategory>
#include <QQuickItem>

DS_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(dsLog)

class DPanelViewPrivate
{
public:
    DPanelViewPrivate()
    {
    }
    Types::Location m_location;
    Types::Position m_position;
};

DPanelView::DPanelView(QQuickWindow *window)
    : QObject(window)
    , d(new DPanelViewPrivate())
{
}

DPanelView::~DPanelView()
{

}

QQuickWindow *DPanelView::window() const
{
    return qobject_cast<QQuickWindow *>(parent());
}

DPanelView *DPanelView::qmlAttachedProperties(QObject *object)
{
    QQuickWindow *window = qobject_cast<QQuickWindow *>(object);
    if (window) {
        return new DPanelView(window);
    }

    return nullptr;
}

void DPanelView::positionPanel()
{
    QRect rect = window()->geometry();
    auto screen = window()->screen();
    switch(d->m_position) {
    case Types::CenterPositioned: {
        rect.moveCenter(screen->geometry().center());
    } break;
    case Types::TopPositioned: {
        rect.moveTop(screen->geometry().top());
    } break;
    case Types::BottomPositioned: {
        rect.moveBottom(screen->geometry().bottom());
    } break;
    default:
        break;
    }

    if (rect != window()->geometry()) {
        window()->setGeometry(rect);
    }
}

Types::Location DPanelView::location() const
{
    return d->m_location;
}

void DPanelView::setLocation(const Types::Location &newLocation)
{
    if (d->m_location == newLocation)
        return;
    d->m_location = newLocation;
    emit locationChanged();
}

Types::Position DPanelView::position() const
{
    return d->m_position;
}

void DPanelView::setPosition(const Types::Position &newPosition)
{
    if (d->m_position == newPosition)
        return;
    d->m_position = newPosition;
    positionPanel();
    emit positionChanged();
}


DS_END_NAMESPACE
