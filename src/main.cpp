#include "login.h"
#include "signup.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login loginPage;
    loginPage.show();


    return a.exec();
}
