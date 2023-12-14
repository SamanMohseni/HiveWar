#include "SinglePlayer.h"
#include <QDebug>

SinglePlayer::SinglePlayer() {
    CreateServer();
    CreateGameManager();
    CreateAI();

    QTimer * turn_time = new QTimer();
    connect(turn_time,SIGNAL(timeout()),this,SLOT(FillServerDesireMap()));
    turn_time->start(server->TurnTime() * 1000);
}

void SinglePlayer::CreateServer() {
    server = new Server();
    map = server->GetMap();
    desire_map = server->GetDesireMap();
}

void SinglePlayer::CreateGameManager() {
    game_manager = new GameManager(map, server->TurnTime());

}

void SinglePlayer::CreateAI() {
    ai_map = new Map(map->Width(), map->Height());
    CopyMap();
    ai = new AI(ai_map);
    ai->Run();
}

void SinglePlayer::Update() {
    //modify hexagon in server.
    game_manager->ClearScreen();
    server->Analyze();
    game_manager->Refresh();
    CopyMap();
    ai->Run();
}

void SinglePlayer::CopyMap() {
    for (int i = 0; i < map->Width(); i++){
        for (int j = 0; j < map->Height(); j++){
            ai_map->Get(i, j)->Clear();
            ai_map->Get(i, j)->Insert(map->Get(i, j)->ObjectInside());
            if(!map->Get(i, j)->IsCenteral()){
                ai_map->Get(i, j)->SetAsSideHexagon();
            }
        }
    }
}

void SinglePlayer::FillServerDesireMap() {
    OBJECT_TYPE object_type;
    GameObject * game_object;
    Request request;
    Map * tmp_map;
    for(int n = 0; n < 2; n++) {
        if(n == 0){
            tmp_map = map;
        }
        else{
            tmp_map = ai_map;
        }
        for (int i = 0; i < map->Width(); i++){
            for (int j = 0; j < map->Height(); j++){
                if(tmp_map->Get(i, j)->IsCenteral()){
                    game_object = tmp_map->Get(i, j)->ObjectInside();
                    if(game_object != NULL && game_object->GetID() == n){
                        object_type = game_object->GetObjectType();

                        request.ID = game_object->GetID();//id might be useless due to servers access to map.
                        request.location = game_object->GetLocation();
                        switch (object_type) {
                        case type_worker:
                            if(game_object->NextLocation() != QPair<int, int>(-1, -1)) {
                                qDebug()<<"worker move request";
                                request.task_id = task_move;
                                desire_map->GetDesire(game_object->NextLocation())->desire.push_back(request);
                            }
                            else if(game_object->GetTarget() != QPair<int, int>(-1, -1)) {
                                switch (game_object->BiuldingType()) {
                                case type_castle:
                                    qDebug()<<"worker biuld castle request";
                                    request.task_id = task_biuld_castle;
                                    break;
                                case type_defencetower:
                                    qDebug()<<"worker biuld defencetower request";
                                    request.task_id = task_biuld_defence_tower;
                                    break;
                                case type_hovel:
                                    qDebug()<<"worker biuld hovel request";
                                    request.task_id = task_biuld_hovel;
                                    break;
                                case type_military_home:
                                    qDebug()<<"worker biuld military home request";
                                    request.task_id = task_biuld_military_house;
                                    break;
                                case type_biulding:
                                    qDebug()<<"worker complete biulding request";
                                    request.task_id = task_complete_biulding;
                                    break;
                                default://extraction:
                                    qDebug()<<"worker extraction request";
                                    request.task_id = task_extraction;
                                }
                                desire_map->GetDesire(game_object->GetTarget())->desire.push_back(request);
                            }
                            break;
                        case type_soldier:
                            if(game_object->NextLocation() != QPair<int, int>(-1, -1)) {
                                qDebug()<<"soldier move request";
                                request.task_id = task_move;
                                desire_map->GetDesire(game_object->NextLocation())->desire.push_back(request);
                            }
                            else if(game_object->GetTarget() != QPair<int, int>(-1, -1)) {
                                qDebug()<<"soldier attack request";
                                request.task_id = task_remote_attack;
                                desire_map->GetDesire(game_object->GetTarget())->desire.push_back(request);
                            }
                            break;
                        case type_defencetower:
                            request.task_id = task_remote_attack;
                            for(int k = 0; k < game_object->GetTargets()->size(); k++) {
                                qDebug()<<"defencetower shoot request";
                                desire_map->GetDesire((*(game_object->GetTargets()))[k])->desire.push_back(request);//to recheck.
                            }
                            break;
                        case type_castle:
                            request.task_id = task_remote_attack;
                            for(int k = 0; k < game_object->GetTargets()->size(); k++) {
                                qDebug()<<"castle shoot request to:"<<(*(game_object->GetTargets()))[k];
                                desire_map->GetDesire((*(game_object->GetTargets()))[k])->desire.push_back(request);//to recheck.
                                qDebug()<<desire_map->GetDesire((*(game_object->GetTargets()))[k])->desire.size();
                            }
                            break;
                        case type_hovel:
                            request.task_id = task_create_people;
                            for(int k = 0; k < game_object->GetTargets()->size(); k++) {
                                qDebug()<<"hovel worker creation request";
                                desire_map->GetDesire((*(game_object->GetTargets()))[k])->desire.push_back(request);//to recheck.
                            }
                            break;
                        case type_military_home:
                            request.task_id = task_create_soldier;
                            for(int k = 0; k < game_object->GetTargets()->size(); k++) {
                                qDebug()<<"military home soldier creation request";
                                desire_map->GetDesire((*(game_object->GetTargets()))[k])->desire.push_back(request);//to recheck.
                            }
                            break;
                        }
                        game_object->ClearDesire();
                    }
                }
            }
        }
    }
    Update();
}


SinglePlayerIcon::SinglePlayerIcon(){
    setPixmap(QPixmap(":/images/Play.png"));
}

void SinglePlayerIcon::mousePressEvent(QGraphicsSceneMouseEvent * event){
    new SinglePlayer();
}
