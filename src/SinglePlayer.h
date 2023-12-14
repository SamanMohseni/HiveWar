#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QObject>
#include <QTimer>

#include "GameManagerProxy.h"
#include "GameManager.h"
#include "DesireMap.h"
#include "Server.h"
#include "Map.h"
#include "AI.h"

extern GameManagerProxy * game_manager_proxy;

class SinglePlayer:public QObject {
    Q_OBJECT
public:
    SinglePlayer();
private:
    void CreateServer();//map and server and desire_map are filled here.
    void CreateGameManager();//sends map to GameManager. filles game_manager.
    void CreateAI();//creates ai map by copying. sends ai_map to AI. filles ai.

    void Update();//calls GameManager Update function. refreshes the copy of map for AI. runs Ai.
    void CopyMap();
private slots:
    void FillServerDesireMap();//after each turns copyes maps data to DesireMap to be analysed. commands the server to analyze data.
    //and runs Update function.
private:
    Server * server;
    Map * map;//== Player map
    Map * ai_map;//a copy of map for AI.
    DesireMap * desire_map;
    GameManager * game_manager;
    AI * ai;
};

class SinglePlayerIcon : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    SinglePlayerIcon();
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif // SINGLEPLAYER_H
