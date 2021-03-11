#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>


#include "login.h"

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_signupButton_clicked();

private:
    Ui::SignUp *ui;
    Login *loginPage;
    QSqlDatabase database;
};

#endif // SIGNUP_H
