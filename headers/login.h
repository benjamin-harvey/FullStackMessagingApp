#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>


#define SQLDB "QMYSQL"
#define HOST "127.0.0.1"
#define USER "admin"
#define PASSWORD "3GlWMCkAaHwd"
#define DB_NAME "qt5"
#define TB_NAME "users"

class SignUp;
class MessagingWindow;

extern std::string usernameExtern;

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_signupButton_clicked();

    void on_passwordInput_returnPressed();

    void on_usernameInput_returnPressed();

private:
    Ui::Login *ui;
    SignUp *signUpPage;
    MessagingWindow *messengerWindow;
    QSqlDatabase database;
};
#endif // LOGIN_H
