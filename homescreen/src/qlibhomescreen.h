/*
 * Copyright (c) 2017 TOYOTA MOTOR CORPORATION
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef QLIBHOMESCREEN_H
#define QLIBHOMESCREEN_H

#include <QObject>
#include <libhomescreen.hpp>
#include <functional>
#include <QVariant>

class QLibHomeScreen : public QObject
{
    Q_OBJECT
public:
    explicit QLibHomeScreen(QObject *parent = 0);
    ~QLibHomeScreen();

    QLibHomeScreen(const QLibHomeScreen &) = delete;
    QLibHomeScreen &operator=(const QLibHomeScreen &) = delete;

    enum QEventType {
       Event_TapShortcut = LibHomeScreen::Event_TapShortcut,
       Event_ShowWindow = LibHomeScreen::Event_ShowWindow,
       Event_OnScreenMessage = LibHomeScreen::Event_OnScreenMessage,
       Event_OnScreenReply = LibHomeScreen::Event_OnScreenReply,
       Event_HideWindow = LibHomeScreen::Event_HideWindow,
       Event_ReplyShowWindow = LibHomeScreen::Event_ReplyShowWindow,
       Event_ShowNotification = LibHomeScreen::Event_ShowNotification,
       Event_ShowInformation = LibHomeScreen::Event_ShowInformation
    };
    using handler_fun = std::function<void(json_object *object)>;

    void init(int port, const QString &token);
    void set_event_handler(enum QEventType et, handler_fun f);
    void showWindow(QString application_id, json_object* area);
    void replyShowWindow(QString application_id, json_object* reply);
    Q_INVOKABLE void showInformation(QString info);
    Q_INVOKABLE void showNotification(QString icon, QString text);

    Q_INVOKABLE int onScreenMessage(const QString &message);
    Q_INVOKABLE int subscribe(const QString &eventName);
    Q_INVOKABLE int unsubscribe(const QString &eventName);
    Q_INVOKABLE void tapShortcut(QString application_id);
    Q_INVOKABLE void showWindow(QString application_id, QString area);
    Q_INVOKABLE void hideWindow(QString application_id);
    Q_INVOKABLE void replyShowWindow(QString application_id, QString reply);

signals:

private:
    LibHomeScreen *mp_hs;
};

#endif // QLIBHOMESCREEN_H
