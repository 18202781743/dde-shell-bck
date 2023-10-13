// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include <QObject>

DS_BEGIN_NAMESPACE

class Types : public QObject
{
    Q_OBJECT
public:
    Types(QObject *parent = nullptr);
    enum Location {
        Floating = 0, /**< Free floating. Neither geometry or z-ordering
                     is described precisely by this value. */
        Desktop, /**< On the planar desktop layer, extending across
                the full screen from edge to edge */
        FullScreen, /**< Full screen */
        TopEdge, /**< Along the top of the screen*/
        BottomEdge, /**< Along the bottom of the screen*/
        LeftEdge, /**< Along the left side of the screen */
        RightEdge, /**< Along the right side of the screen */
    };
    Q_ENUM(Location)

    enum Position {
        LeftPositioned, /**< Positioned left */
        RightPositioned, /**< Positioned right */
        TopPositioned, /**< Positioned top */
        BottomPositioned, /**< Positioned bottom */
        CenterPositioned, /**< Positioned in the center */
    };
    Q_ENUM(Position)
};

DS_END_NAMESPACE