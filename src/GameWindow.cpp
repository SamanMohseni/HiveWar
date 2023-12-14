#include "GameWindow.h"
#include <QDebug>

GameWindow::GameWindow() {
    setPixmap(QPixmap(":/images/GameWindow.png"));
    setPos(0, 0);
    setZValue(120);
}

void GameWindow::Draw(QGraphicsScene * _scene) {
    scene = _scene;
    scene->addItem(this);
}

void GameWindow::ShowInfo(GameObject *_game_object) {
    qDebug()<<"ObjectType: "<<_game_object->GetObjectType();
    qDebug()<<"Location: "<<_game_object->GetLocation();
    qDebug()<<"Health: "<<_game_object->GetHealth();
    qDebug()<<"Stamina: "<<_game_object->GetStamina();
    //...
}

void GameWindow::Update() {

}
