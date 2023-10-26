// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "applet.h"

#include <QQmlListProperty>

DS_BEGIN_NAMESPACE

class DPItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString iconName READ iconName CONSTANT)
    Q_PROPERTY(int mode READ mode CONSTANT)
    Q_PROPERTY(QString key READ key CONSTANT)
public:
    DPItem(const QString &text, const QString &iconName, int mode, QObject *parent = nullptr);
    DPItem(const QString &text, const QString &name, const QString &iconName, int mode, QObject *parent = nullptr);
    enum DPMode{
        Merge,
        Extend,
        Single
    };
    Q_ENUM(DPMode);

    QString text() const;
    QString name() const;
    QString iconName() const;
    int mode() const;
    QString key() const;

Q_SIGNALS:
    void textChanged();
    void iconNameChanged();
    void modeChanged();

private:
    QString m_text;
    QString m_name;
    QString m_iconName;
    int m_mode;

};

class Q_DECL_EXPORT DisPlayModeApplet : public DApplet
{
    Q_OBJECT
    Q_PROPERTY(int state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(DPItem *currentPlanItem READ currentPlanItem NOTIFY currentPlanItemChanged FINAL)
    Q_PROPERTY(QQmlListProperty<DPItem> planItems READ planItems NOTIFY planItemsChanged FINAL)
public:
    explicit DisPlayModeApplet(QObject *parent = nullptr);
    virtual void init() override;

    int state() const;
    DPItem *currentPlanItem() const;
    QQmlListProperty<DPItem> planItems();

Q_SIGNALS:
    void currentPlanItemChanged();
    void planItemsChanged();

    void stateChanged();

private:
    void setState(int newState);
    void setCurrentPlanItem(DPItem *newCurrentPlanItem);
    void fetchPlanItems();
    DPItem *fetchCurrentPlanItem() const;
    int fetchState() const;

private:
    QList<DPItem *> m_planItems;
    DPItem *m_currentPlanItem = nullptr;
    int m_state;
};

DS_END_NAMESPACE
