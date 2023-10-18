// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "dstypes.h"

#include <QQuickWindow>

DS_BEGIN_NAMESPACE

class DPluginMetaData;
/**
 * @brief 插件项
 */
class DPanelViewPrivate;
class Q_DECL_EXPORT DPanelView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickWindow* window READ window FINAL)
    Q_PROPERTY(DS_NAMESPACE::Types::Location location READ location WRITE setLocation NOTIFY locationChanged FINAL)
    Q_PROPERTY(DS_NAMESPACE::Types::Position position READ position WRITE setPosition NOTIFY positionChanged FINAL)
public:
    DPanelView(QQuickWindow *window = nullptr);
    virtual ~DPanelView();

    QQuickWindow *window() const;

    Types::Location location() const;
    void setLocation(const Types::Location &newLocation);

    static DPanelView *qmlAttachedProperties(QObject *object);

    Types::Position position() const;
    void setPosition(const Types::Position &newPosition);

Q_SIGNALS:
    void locationChanged();

    void positionChanged();

private:
    void positionPanel();

private:
    DPanelViewPrivate *d = nullptr;
};

DS_END_NAMESPACE

QML_DECLARE_TYPEINFO(DS_NAMESPACE::DPanelView, QML_HAS_ATTACHED_PROPERTIES)
