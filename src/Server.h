#ifndef SERVER_H
#define SERVER_H

#include "FileManager.h"
#include "SystemInfo.h"
#include "DesireMap.h"
#include "Desire.h"
#include "Map.h"

class ExtractDesire {
public:
    ExtractDesire(Desire * _desire);
    bool HasRequest(TaskID _task_id,int _id);
private:
    Desire * desire;
};

class Server {
public:
    Server();//Loades Game.
    //void SaveGame();
    Map * GetMap();
    DesireMap * GetDesireMap();
    int TurnTime();
    void Analyze();//creates new objects. delets some objects. Updates map content.
private:
    void LoadGame();//creates a FileManager. loads map. create a DesireMap.
    void CopyMap();
    GameObject * RunTask(Desire * _desire, int _id);
    void HandleRequestsInBiuldingBase(QPair<int, int> _center, int _radious);
    void DoRemoteAttacks(QPair<int, int> _location);
    void DoExtraction(QPair<int, int> _location);
    void DoCompleteBiulding(QPair<int, int> _location);
private:
    Map * map;
    Map * original_map;
    DesireMap * desire_map;
    double turn_time;
    FileManager * file_manager;
    int ** analyze_map;
    int ** biuld_validity;
    bool ** remote_attack;
};

#endif // SERVER_H
