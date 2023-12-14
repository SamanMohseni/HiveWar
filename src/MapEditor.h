#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QObject>
#include <QVector>
#include <QTimer>

#include "GameManagerProxy.h"
#include "FileManager.h"
#include "Buttons.h"
#include "Map.h"

extern Button * *all_buttons;

extern GameManagerProxy * game_manager_proxy;

class MapEditor : public QObject {
    Q_OBJECT
public:
    MapEditor();
private slots:
    void CheckProxy();
    void ScrollContent();
private:
    Map * map;
    QGraphicsScene * scene;
    QGraphicsView * view;
    FileManager * file_manager;
    GameObject * game_object;
    int id;
    int Vertical_scroll_id, Horizontal_scroll_id;
};

class MapEditorIcon : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    MapEditorIcon();
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif // MAPEDITOR_H
