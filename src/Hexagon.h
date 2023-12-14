#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPair>

#include "GameManagerProxy.h"
#include "AllGameObjects.h"
#include "SystemInfo.h"

extern GameManagerProxy * game_manager_proxy;

class Hexagon : public QObject , public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Hexagon();

    void SetLocation(QPair <int, int> _location);
    void Insert(GameObject *_game_object);
    void Reserve(GameObject *_comming_item);

    void SetPosition();//sets geomatical position based on hexagon index(locatin).
    void MoveOnScreen(double _D_X, double _D_Y);

    void Highlight();
    void EraseHighlight();
    void ItemIsLeaving();
    void SetAsSideHexagon();
    void SetAsCenteral();

    void Clear();

    QPair <int, int> GetLocation();
    GameObject *ObjectInside();
    GameObject *CommingObject();

    bool IsCenteral();
    bool IsComming();
    bool IsHighlighted();
    bool ItemHasLeft();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);//reports its self. to GameManagerProxy
private:
    bool is_centeral;//of multi hexagon objects.
    bool is_highlighted;
    bool is_comming;
    bool item_has_left;
    QPair <int, int> location;
    GameObject *game_object;
    GameObject *comming_item;//these two may be use less and might be changed too a bool is_empty_in_next maybe.
};

#endif // HEXAGON_H
