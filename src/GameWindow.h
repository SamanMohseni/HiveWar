#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "FixedPositionObject.h"
#include "AllGameObjects.h"
#include "Buttons.h"

class GameWindow : public FixedPositionObject {
public:
    GameWindow();
    void Draw(QGraphicsScene * _scene);
    void ShowInfo(GameObject * _game_object);

private slots:
    void Update();
private:
    QGraphicsScene * scene;
};

#endif // GAMEWINDOW_H
