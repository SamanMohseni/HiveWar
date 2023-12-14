#ifndef FIXEDPOSITIONOBJECT_H
#define FIXEDPOSITIONOBJECT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPair>

#include "GameManagerProxy.h"

extern GameManagerProxy * game_manager_proxy;

class FixedPositionObject: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    FixedPositionObject();
    void setPos(int _x, int _y);
private slots:
    void MatchScreen();
private:
    QPair <int, int> scene_rect_deviation;
    int original_x, original_y;

};

#endif // FIXEDPOSITIONOBJECT_H
