
#include <QApplication>
#include "UI/Login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*    Main main;
    main.show();*/
    Login login;
    login.show();
    return a.exec();
}
