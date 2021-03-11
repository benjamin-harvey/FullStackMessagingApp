
#include "ui_login.h"
#include "signup.h"
#include "login.h"
#include "messagingwindow.h"
#include "user.h"


std::string usernameExtern;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->usernameInput->setPlaceholderText("Enter your username");
    ui->passwordInput->setPlaceholderText("Enter your password");

}

Login::~Login()
{
    delete ui;
}


void Login::on_loginButton_clicked()
{

    QSqlDatabase db = QSqlDatabase::addDatabase(SQLDB);
    db.setHostName(HOST);
    db.setUserName(USER);
    db.setPassword(PASSWORD);
    db.setDatabaseName(DB_NAME);

    if (db.open()){

        QString username = ui->usernameInput->text();
        std::string passwordInput = ui->passwordInput->text().toStdString();

        for(int i = 0; i < 100 && passwordInput[i] != '\0'; i++){
            passwordInput[i] = passwordInput[i] + 2;
        }

        QString password = QString::fromStdString(passwordInput);


        QSqlQuery query(QSqlDatabase::database("MyConnect"));

        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));

        query.bindValue(":username", username);
        query.bindValue(":password", password);

        query.exec();
        if(query.next()){
            QMessageBox::information(this, "Successful", "Login successful");

            std::string userNameToString = username.toStdString();

            usernameExtern = userNameToString;

            messengerWindow = new MessagingWindow();
            messengerWindow->show();
            this->close();

        }
        else {
            QMessageBox::information(this, "Failed", "Login failed");
        }
    }

    else {
        QMessageBox::information(this, "Not Connected", "Database is not connected");
    }
}

void Login::on_signupButton_clicked()
{
    signUpPage = new SignUp();
    signUpPage->show();
    this->close();


}

void Login::on_passwordInput_returnPressed()
{
    on_loginButton_clicked();
}

void Login::on_usernameInput_returnPressed()
{
    on_loginButton_clicked();
}
