#include <QApplication>
#include <QVector>

#include <QDebug>

#include "GameManagerProxy.h"
#include "MainMenu.h"
#include "Buttons.h"

GameManagerProxy * game_manager_proxy;

QVector <Button *> on_screen;

Button * *all_buttons;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    all_buttons = new Button *[32];
    new MainMenu();

    return a.exec();
}
