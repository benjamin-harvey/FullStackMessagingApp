#include "headers/messagingwindow.h"
#include "ui_messagingwindow.h"
#include "headers/user.h"
#include "headers/login.h"


MessagingWindow::MessagingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessagingWindow)
{
    ui->setupUi(this);


    //User* firstman;
    //QString userName = QString::fromStdString(firstman->name);

    QString userName = QString::fromStdString(usernameExtern);

    ui->actualDisplayName->setText(userName);
    ui->actualUsername->setText(userName);

    ui->inputMessage->setEnabled(false);
    ui->submitButton->setEnabled(false);
    ui->fileButton->setEnabled(false);

    QSqlDatabase db = QSqlDatabase::addDatabase(SQLDB);
    db.setHostName(HOST);
    db.setUserName(USER);
    db.setPassword(PASSWORD);
    db.setDatabaseName(DB_NAME);

    m_client = new QMqttClient(this);
    m_client->setHostname(ui->hostInput->text());
    m_client->setPort(ui->portSpinBox->value());

    m_client->setClientId(ui->actualDisplayName->text());

    connect(m_client, &QMqttClient::stateChanged, this, &MessagingWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MessagingWindow::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message) {
        //User* firstman;
        //const QString userName = QString::fromStdString(firstman->name);
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" - ")
                    + m_client->clientId()
                    + QLatin1String(": ")
                    + message
                    + QLatin1Char('\n');
        ui->messagingOutput->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        ui->messagingOutput->insertPlainText(content);
    });

    connect(ui->hostInput, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->portSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MessagingWindow::setClientPort);
    updateLogStateChange();



}

MessagingWindow::~MessagingWindow()
{
    delete ui;

}

void MessagingWindow::on_connectButton_clicked()
{
    // if connected change the box to disconnect and port/host input disabled
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->hostInput->setEnabled(false);
        ui->portSpinBox->setEnabled(false);
        ui->connectButton->setText(tr("Disconnect"));
        m_client->connectToHost();

        // creates holder chats to test the program
        ui->chatSearch->addItem("GeneralChat");
        ui->chatSearch->addItem("AnotherChat");


    } else {
        // set the host/port input to be enabled and change connection button text
        ui->hostInput->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
        ui->connectButton->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }

}

void MessagingWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
    ui->messagingOutput->insertPlainText(content);
}


void MessagingWindow::setClientPort(int p)
{
    m_client->setPort(p);
}


void MessagingWindow::brokerDisconnected()
{
    ui->hostInput->setEnabled(true);
    ui->portSpinBox->setEnabled(true);
    ui->connectButton->setText(tr("Connect"));
}



void MessagingWindow::on_submitButton_clicked()
{

    if (m_client->publish(ui->chatSearch->currentItem()->text(), ui->inputMessage->text().toUtf8()) == -1){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
    }
}

void MessagingWindow::on_inputMessage_returnPressed()
{
    on_submitButton_clicked();
}


void MessagingWindow::on_chatSearch_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "Clicked" << item->text();




    // ui->messagingOutput->clear();

    ui->inputMessage->setEnabled(true);
    ui->submitButton->setEnabled(true);
    ui->fileButton->setEnabled(true);

    auto subscription = m_client->subscribe(ui->chatSearch->currentItem()->text());
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }

}



