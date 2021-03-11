
#include "ui_signup.h"
#include "signup.h"
#include "login.h"

SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    ui->emailInput->setPlaceholderText("Enter your email");
    ui->usernameInput->setPlaceholderText("Enter your username");
    ui->passwordInput->setPlaceholderText("Enter your password");
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_signupButton_clicked()
{

    database = QSqlDatabase::addDatabase(SQLDB);
    database.setHostName(HOST);
    database.setUserName(USER);
    database.setPassword(PASSWORD);
    database.setDatabaseName(DB_NAME);

    if(database.open()){
        // Retreive data from input fields
        QString emailInput = ui->emailInput->text();
        QString usernameInput = ui->usernameInput->text();

        std::string passwordHolder = ui->passwordInput->text().toStdString();

        // password encrypter
        for(int i = 0; i < 100 && passwordHolder[i] != '\0'; i++){
            passwordHolder[i] = passwordHolder[i] + 2;
        }


        QString passwordInput = QString::fromStdString(passwordHolder);

        std::cout << passwordHolder << std::endl;



        // run out insert query
        QSqlQuery qry;
        QString sql_sentence = "INSERT INTO ";
        sql_sentence += TB_NAME;
        sql_sentence += "(email, username, password) VALUES (:email, :username, :password)";

        qry.prepare(sql_sentence);

        qry.bindValue(":email", emailInput);
        qry.bindValue(":username", usernameInput);
        qry.bindValue(":password", passwordInput);

        if(qry.exec()){
            QMessageBox::information(this, "Inserted", "Data Inserted Successful");
        }
        else {
            QMessageBox::information(this, "Not Inserted", "Data Inserted Unsuccessful");
        }

    }
    else {
        QMessageBox::information(this, "Not connected", "Database is not connected");
    }

    this->close();
    loginPage = new Login();
    loginPage->show();
}
