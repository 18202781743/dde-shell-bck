// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "applet.h"

DS_BEGIN_NAMESPACE

class Q_DECL_EXPORT DisPlayModeApplet : public DApplet
{
    Q_OBJECT
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged FINAL)
    Q_PROPERTY(int displayMode READ displayMode WRITE setDisplayMode NOTIFY displayModeChanged FINAL)
    Q_PROPERTY(QString primaryScreen READ primaryScreen WRITE setPrimaryScreen NOTIFY primaryScreenChanged FINAL)
    Q_PROPERTY(QStringList outputNames READ outputNames WRITE setOutputNames NOTIFY outputNamesChanged FINAL)
public:
    explicit DisPlayModeApplet(QObject *parent = nullptr);
    virtual void init() override;

    int state() const;
    void setState(int newState);

    int displayMode() const;
    void setDisplayMode(int newDisplayMode);

    QString primaryScreen() const;
    void setPrimaryScreen(const QString &newPrimaryScreen);

    QStringList outputNames() const;
    void setOutputNames(const QStringList &newOutputNames);

Q_SIGNALS:

    void stateChanged();

    void displayModeChanged();

    void primaryScreenChanged();

    void outputNamesChanged();

private:
    int m_state = 2;
    int m_displayMode;
    QString m_primaryScreen;
    QStringList m_outputNames {"A1", "A2"};
};

DS_END_NAMESPACE
