#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPolygonF>
#include <qmath.h>
#include <QVector>
#include <QObject>
#include <QTimer>
#include <QPair>

#include "GameManagerProxy.h"
#include "AllGameObjects.h"
#include "SystemInfo.h"
#include "GameWindow.h"
#include "Buttons.h"
#include "Map.h"

extern GameManagerProxy * game_manager_proxy;

extern QVector <Button *> on_screen;

                   //GameManager is created by Single(Multi)Player.
class GameManager : public QObject {//the scene most be created here.
    Q_OBJECT
public:
    GameManager(Map * _map, int _timeout);//...//create all buttons, set their GameManager.
    void Refresh();
    void ClearScreen();
private:
    void Suspend(GameObject *_suspended_item);//if the item was tasked before cancel it.
    void Report(QPair <int, int> _reporter_item);
    //when we have both suspended_item and reporter_item we can UpdateSuspendAndReporterItem() some info in both items.
    //if didnt chose any button, the first button is by default set.
    void ButtonCommand(int _button_id);
    void HighLightForWorker(QPair<int, int> _center, int _biulding_radious);
    void DrawLine(QPair<int, int> _first_location, QPair<int, int> _next_location, int _color);

    void UpdateSuspendAndReporterItem();
    //void CancelTask();
    void TaskClear();

private slots:
    void CheckProxy();
    void ScrollContent();

private:
    Map * map;
    GameObject * suspended_item;
    QPair <int, int> reporter_item;
    QGraphicsScene * scene;
    GameWindow * game_window;
    QGraphicsView * view;
    QVector<Hexagon *> highlighted_hexagons;
    QVector<QGraphicsPolygonItem *> on_screen_lines;
    int button_id;
    int timeout;
    int Vertical_scroll_id, Horizontal_scroll_id;
    bool in_task_mode;
};

#endif // GAMEMANAGER_H
