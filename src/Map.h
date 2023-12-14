#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPair>

#include "Hexagon.h"

class Map {
public:
    Map(int _width, int _height);
    Hexagon * Get(int x, int y);
    Hexagon * Get(QPair<int, int> _location);

    QVector<QPair<int, int> > * GetHexagonsAround(QPair<int, int> _location,int _from_radious,int _untill_radious);
    void InsertObjectsAround(GameObject * _game_object, QPair<int, int> _location,int _from_radious,int _untill_radious);
    void RemoveObjectsAround(QPair<int, int> _location,int _from_radious,int _untill_radious);
    void Draw(QGraphicsScene * _scene);
    void Clear(QGraphicsScene * _scene);
    void DrawOneItem(QPair<int, int> _location, QGraphicsScene * _scene);
    int Width();
    int Height();
private:
    void SizeAllocate();
private:
    QVector<QPair<int, int> > neighbours;
    int move_structure[6][2];
    Hexagon * ** map;
    int width, height;
};

#endif // MAP_H
