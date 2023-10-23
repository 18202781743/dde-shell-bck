// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "corona.h"

DS_BEGIN_NAMESPACE

class Q_DECL_EXPORT OsdCorona : public DCorona
{
    Q_OBJECT
    Q_PROPERTY(QString iconName READ iconName NOTIFY iconNameChanged FINAL)
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged FINAL)
    Q_PROPERTY(QString osdType READ osdType NOTIFY osdTypeChanged FINAL)
    Q_CLASSINFO("D-Bus Interface", "org.deepin.osdService")
public:
    explicit OsdCorona(QObject *parent = nullptr);

    virtual void init() override;

    bool visible() const;
    QString osdType() const;

    QString iconName() const;

public Q_SLOTS:
    void showText(const QString &text);

Q_SIGNALS:
    void visibleChanged();
    void iconNameChanged();
    void osdTypeChanged();

private Q_SLOTS:
    void hideOsd();
private:
    void showOsd();
    void setVisible(const bool visible);
    void setIconName(const QString &iconName);
    void setOsdType(const QString &osdType);

private:
    bool m_visible;
    QTimer *m_osdTimer = nullptr;
    QString m_iconName;
    QString m_osdType {"SwitchMonitors"};
};

DS_END_NAMESPACE
