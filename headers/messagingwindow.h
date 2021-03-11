#ifndef MESSAGINGWINDOW_H
#define MESSAGINGWINDOW_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QListWidget>
#include <QMqttClient>

#include <QtWidgets/QMessageBox>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QDebug>

#include "login.h"


class User;

namespace Ui {
class MessagingWindow;
}

class MessagingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MessagingWindow(QWidget *parent = nullptr);
    ~MessagingWindow();

public slots:
    void setClientPort(int p);

private slots:
    void on_connectButton_clicked();
    void updateLogStateChange();
    void brokerDisconnected();

    void on_submitButton_clicked();

    void on_chatSearch_itemDoubleClicked(QListWidgetItem *item);

    void on_inputMessage_returnPressed();


private:
    Ui::MessagingWindow *ui;
    QMqttClient *m_client;
};

#endif // MESSAGINGWINDOW_H
