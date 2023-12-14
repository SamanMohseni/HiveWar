#include "Server.h"
#include<QDebug>


ExtractDesire::ExtractDesire(Desire *_desire) {
    desire = _desire;
}

bool ExtractDesire::HasRequest(TaskID _task_id, int _id) {
    TaskID biuld_tasks[4]={task_biuld_castle, task_biuld_defence_tower, task_biuld_hovel, task_biuld_military_house};
    if(_task_id == task_biuld){
        for(int n = 0; n < 4; n++){
            for(int i = 0; i < desire->desire.size(); i++){
                if(desire->desire[i].task_id == biuld_tasks[n] && desire->desire[i].ID == _id){
                    qDebug()<<"had request!";
                    return true;
                }
            }
        }
    }
    else{
        for(int i = 0; i < desire->desire.size(); i++){
            if(desire->desire[i].task_id == _task_id && desire->desire[i].ID == _id){
                qDebug()<<"had request!";
                return true;
            }
        }
    }
    return false;
}


Server::Server() {
    file_manager = new FileManager();
    LoadGame();

    original_map = new Map(map->Width(), map->Height());

    //allocate analyze_map array.
    analyze_map = new int *[map->Width()];
    for (int i = 0; i < map->Width(); i++){
        analyze_map[i] = new int [map->Height()];
        for(int j = 0; j < map->Height(); j++){
            analyze_map[i][j]=0;
        }
    }

    //allocate biuld_validity array.
    biuld_validity = new int *[map->Width()];
    for (int i = 0; i < map->Width(); i++){
        biuld_validity[i] = new int [map->Height()];
        for(int j = 0; j < map->Height(); j++){
            biuld_validity[i][j]=0;
        }
    }

    //allocate remote_attack array.
    remote_attack = new bool *[map->Width()];
    for (int i = 0; i < map->Width(); i++){
        remote_attack[i] = new bool [map->Height()];
        for(int j = 0; j < map->Height(); j++){
            remote_attack[i][j]=0;
        }
    }

    turn_time = 15;//for example.
}

Map *Server::GetMap() {
    return map;
}

DesireMap *Server::GetDesireMap() {
    return desire_map;
}

int Server::TurnTime() {
    return turn_time;
}

void Server::Analyze() {//the brain of this game.//for now it is assumed that all desires are valid, so there will be no validity check.
    CopyMap();
    //reset analyze arrays.
    for (int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            analyze_map[i][j]=0;
            biuld_validity[i][j]=0;
            remote_attack[i][j]=0;
        }
    }
    qDebug()<<"Analying Requests...";
    Desire *tmp;
    QVector<QPair<int, int> > *base_hexagon;
    QPair<int, int> location;
    int radious;
    GameObject * player_1;
    GameObject * player_2;

    //findin valid places for biulding.
    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            tmp = desire_map->GetDesire(i, j);
            for(int k = 0; k < tmp->desire.size(); k++){
                if(tmp->desire[k].task_id == task_biuld_castle || tmp->desire[k].task_id == task_biuld_defence_tower || tmp->desire[k].task_id == task_biuld_hovel || tmp->desire[k].task_id == task_biuld_military_house){
                    location = QPair<int, int>(i, j);
                    switch (tmp->desire[k].task_id) {
                    case task_biuld_castle:
                        radious = castle_radious;
                        break;
                    case task_biuld_defence_tower:
                        radious = defense_tower_radious;
                        break;
                    case task_biuld_hovel:
                        radious = hovel_radious;
                        break;
                    case task_biuld_military_house:
                        radious = militaryhome_radious;
                        break;
                    }
                    base_hexagon = map->GetHexagonsAround(location, 1, radious);
                    for(int n = 0; n < base_hexagon->size(); n++){
                        if((*base_hexagon)[n].first >= 0 && (*base_hexagon)[n].first < map->Width() && (*base_hexagon)[n].second >= 0 && (*base_hexagon)[n].second < map->Height()){
                            analyze_map[(*base_hexagon)[n].first][(*base_hexagon)[n].second]++;
                        }
                    }
                    qDebug()<<"biulding part";
                    analyze_map[i][j]++;
                }
            }
        }
    }

    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            tmp = desire_map->GetDesire(i, j);
            for(int k = 0; k < tmp->desire.size(); k++){
                if(tmp->desire[k].task_id == task_biuld_castle || tmp->desire[k].task_id == task_biuld_defence_tower || tmp->desire[k].task_id == task_biuld_hovel || tmp->desire[k].task_id == task_biuld_military_house){
                    location = QPair<int, int>(i, j);
                    switch (tmp->desire[k].task_id) {
                    case task_biuld_castle:
                        radious = castle_radious;
                        break;
                    case task_biuld_defence_tower:
                        radious = defense_tower_radious;
                        break;
                    case task_biuld_hovel:
                        radious = hovel_radious;
                        break;
                    case task_biuld_military_house:
                        radious = militaryhome_radious;
                        break;
                    }
                    base_hexagon = map->GetHexagonsAround(location, 1, radious);
                    for(int n = 0; n < base_hexagon->size(); n++){
                        if((*base_hexagon)[n].first >= 0 && (*base_hexagon)[n].first < map->Width() && (*base_hexagon)[n].second >= 0 && (*base_hexagon)[n].second < map->Height()){
                            if(analyze_map[(*base_hexagon)[n].first][(*base_hexagon)[n].second] > 1){
                                qDebug()<<"invalid place to biuld";
                                biuld_validity[i][j] = 1;//here means false.
                                break;
                            }
                        }
                    }
                    if(analyze_map[i][j] > 1){
                        biuld_validity[i][j] = 1;
                    }
                    if(biuld_validity[i][j] == 1){//not valid.
                        for(int n = 0; n < base_hexagon->size(); n++){
                            if((*base_hexagon)[n].first >= 0 && (*base_hexagon)[n].first < map->Width() && (*base_hexagon)[n].second >= 0 && (*base_hexagon)[n].second < map->Height()){
                                biuld_validity[(*base_hexagon)[n].first][(*base_hexagon)[n].second] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    ExtractDesire * extract_desire;
    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){

            location = QPair<int, int>(i, j);
            tmp = desire_map->GetDesire(location);
            extract_desire = new ExtractDesire(tmp);

            if(analyze_map[i][j] > 0 && biuld_validity[i][j] == 0){//there is gonna be some biulding here.
                //abort all requests exept for biulding, after biulding run all requests in biulding base.
                if(extract_desire->HasRequest(task_biuld, 0) || extract_desire->HasRequest(task_biuld, 1)){
                    qDebug()<<"biulding biulding";
                    for(int request_id = 0; request_id < 2; request_id++){
                        if(extract_desire->HasRequest(task_biuld, request_id)){
                            if(extract_desire->HasRequest(task_biuld_castle, request_id)){
                                HandleRequestsInBiuldingBase(location, castle_radious);
                                qDebug()<<"biulding castle";
                            }
                            else if(extract_desire->HasRequest(task_biuld_defence_tower, request_id)){
                                HandleRequestsInBiuldingBase(location, defense_tower_radious);
                                qDebug()<<"biulding defense_tower";
                            }
                            else if(extract_desire->HasRequest(task_biuld_hovel, request_id)){
                                HandleRequestsInBiuldingBase(location, hovel_radious);
                                qDebug()<<"biulding hovel";
                            }
                            else{//task_biuld_military_house
                                HandleRequestsInBiuldingBase(location, militaryhome_radious);
                                qDebug()<<"biulding militaryhome";
                            }
                        }
                    }
                }
            }
            else{//no new biulding.
                for(int request_id = 0; request_id < 2; request_id++){
                    //fight:
                    player_1 = RunTask(tmp,request_id);
                    player_2 = RunTask(tmp,1 - request_id);
                    if(player_1 != NULL && player_2 != NULL){
                        if(player_1->GetHealth() * player_1->GetStamina() > player_2->GetHealth() * player_2->GetStamina()){
                            player_1->SetHealth((player_1->GetHealth() * player_1->GetStamina() - player_2->GetHealth() * player_2->GetStamina())/player_1->GetStamina());
                            player_1->SetLocation(QPair<int, int> (i, j));
                            map->Get(i, j)->Insert(player_1);
                            DoRemoteAttacks(QPair<int, int> (i, j));//remote attacks.
                            if(player_1->GetHealth() <= 0){
                                map->Get(i, j)->Insert(NULL);//kill.
                                delete player_1;
                            }
                        }
                        else if(player_1->GetHealth() * player_1->GetStamina() < player_2->GetHealth() * player_2->GetStamina()){
                            player_2->SetHealth((player_2->GetHealth() * player_2->GetStamina() - player_1->GetHealth() * player_1->GetStamina())/player_2->GetStamina());
                            player_2->SetLocation(QPair<int, int> (i, j));
                            map->Get(i, j)->Insert(player_2);
                            DoRemoteAttacks(QPair<int, int> (i, j));//remote attacks.
                            if(player_2->GetHealth() <= 0){
                                map->Get(i, j)->Insert(NULL);//kill.
                                delete player_2;
                            }
                        }
                        else{//both die.
                            map->Get(i, j)->Insert(NULL);//kill.
                            delete player_1;
                            delete player_2;
                        }
                    }
                    else if(player_1 != NULL){
                        player_1->SetLocation(QPair<int, int> (i, j));
                        map->Get(i, j)->Insert(player_1);
                        DoRemoteAttacks(QPair<int, int> (i, j));//remote attacks.
                        if(player_1->GetHealth() <= 0){
                            map->Get(i, j)->Insert(NULL);//kill.
                            delete player_1;
                        }
                    }
                    else if(player_2 != NULL){
                        player_2->SetLocation(QPair<int, int> (i, j));
                        map->Get(i, j)->Insert(player_2);
                        DoRemoteAttacks(QPair<int, int> (i, j));//remote attacks.
                        if(player_2->GetHealth() <= 0){
                            map->Get(i, j)->Insert(NULL);//kill.
                            delete player_2;
                        }
                    }
                }
            }
        }
    }
    GameObject * _tmp;
    //remote attacks for static areas.
    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            location = QPair<int, int>(i, j);
            if(remote_attack[i][j] == false){
                _tmp = map->Get(location)->ObjectInside();
                if(_tmp != NULL){
                    DoRemoteAttacks(location);
                    if(_tmp->GetHealth() <= 0){
                        map->RemoveObjectsAround(location, 1, _tmp->GetRadiousOnMap());
                        delete _tmp;
                        map->Get(location)->Insert(NULL);
                    }
                }
            }
        }
    }

    //do extraction & complete biulding
    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            location = QPair<int, int>(i, j);
            tmp = desire_map->GetDesire(location);
            delete extract_desire;
            extract_desire = new ExtractDesire(tmp);

            for(int request_id = 0; request_id < 2; request_id++){
                if(extract_desire->HasRequest(task_complete_biulding, request_id)){
                    _tmp = map->Get(location)->ObjectInside();
                    if(_tmp != NULL){
                        DoCompleteBiulding(location);
                        if(_tmp->GetHealth() >= 100){//for example.
                            switch (_tmp->GetObjectType()) {
                            case type_castle_halfbiuld:
                                _tmp = new Castle();
                                break;
                            case type_defencetower_halfbiuld:
                                _tmp = new DefenseTower();
                                break;
                            case type_hovel_halfbiuld:
                                _tmp = new Hovel();
                                break;
                            case type_military_home_halfbiuld:
                                _tmp = new MilitaryHome();
                                break;
                            }
                            _tmp->SetLocation(location);
                            map->Get(location)->Clear();
                            map->Get(location)->Insert(_tmp);
                            map->InsertObjectsAround(_tmp, location, 1, _tmp->GetRadiousOnMap());
                        }
                    }
                }

                if(extract_desire->HasRequest(task_extraction, request_id)){
                    if(map->Get(location)->ObjectInside() != NULL){
                        DoExtraction(location);
                        if(map->Get(location)->ObjectInside()->GetHealth() <= 0){
                            delete map->Get(location)->ObjectInside();
                            map->Get(location)->Insert(NULL);
                        }
                    }
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////

/*
                if(tmp->desire[k].task_id==task_move){
                    qDebug()<<"running task_move";
                    map->Get(tmp->desire[k].location)->ObjectInside()->SetLocation(QPair<int, int>(i, j));
                    qDebug()<<"reset location";
                    map->Get(i, j)->Insert(map->Get(tmp->desire[k].location)->ObjectInside());
                    map->Get(tmp->desire[k].location)->Insert(NULL);
                }
 */
    //clear junk data in hexagon.
    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            map->Get(i, j)->Clear();
        }
    }
    //refresh map //for now redraw map in GameManager.
    desire_map->Clear();
    qDebug()<<"Analyze Done!";
}

void Server::LoadGame() {
    map = file_manager->LoadData(":/images/map.map");//for example.
    //map = new Map(10, 10);//just for test.
    desire_map = new DesireMap(map->Width(), map->Height());
}

void Server::CopyMap() {
    for (int i = 0; i < map->Width(); i++){
        for (int j = 0; j < map->Height(); j++){
            original_map->Get(i, j)->Clear();
            original_map->Get(i, j)->Insert(map->Get(i, j)->ObjectInside());
            if(!map->Get(i, j)->IsCenteral()){
                original_map->Get(i, j)->SetAsSideHexagon();
            }
        }
    }
}

GameObject *Server::RunTask(Desire * _desire, int _id) {
    GameObject * tmp = NULL;
    for(int i = 0; i < _desire->desire.size(); i++){
        if(_desire->desire[i].ID == _id && _desire->desire[i].task_id != task_remote_attack && _desire->desire[i].task_id != task_extraction){
            switch (_desire->desire[i].task_id) {
            case task_biuld_castle:
                tmp = new CastleHalfBiuld();
                break;
            case task_biuld_defence_tower:
                tmp = new DefenseTowerHalfBiuld();
                break;
            case task_biuld_hovel:
                tmp = new HovelHalfBiuld();
                break;
            case task_biuld_military_house:
                tmp = new MilitaryHomeHalfBiuld();
                break;
            case task_create_people:
                tmp = new Worker;
                break;
            case task_create_soldier:
                tmp = new Soldier();
                break;
            case task_move:
                tmp = map->Get(_desire->desire[i].location)->ObjectInside();
                map->Get(_desire->desire[i].location)->Insert(NULL);//delete object inside.
                break;
            }
            if(tmp != NULL){
                tmp->SetID(_id);
            }
            return tmp;
        }
    }
}

void Server::HandleRequestsInBiuldingBase(QPair<int, int> _center, int _radious) {
    QVector<QPair<int, int> > *base_hexagon;
    GameObject * attacker;
    GameObject * biulding;
    ExtractDesire * extract_desire = new ExtractDesire(desire_map->GetDesire(_center));
    bool will_be_created = true;
    int biulder_id;

    if(extract_desire->HasRequest(task_biuld, 0)){
        biulder_id = 0;
    }
    else{
        biulder_id = 1;
    }

    base_hexagon = map->GetHexagonsAround(_center, 1, _radious);

    for(int n = 0; n < base_hexagon->size(); n++){
        if((*base_hexagon)[n].first >= 0 && (*base_hexagon)[n].first < map->Width() && (*base_hexagon)[n].second >= 0 && (*base_hexagon)[n].second < map->Height()){
            attacker = RunTask(desire_map->GetDesire((*base_hexagon)[n]), 1 - biulder_id);
            if(attacker != NULL){
                attacker->SetLocation((*base_hexagon)[n]);
                attacker->SetLocation((*base_hexagon)[n]);
                map->Get((*base_hexagon)[n])->Insert(attacker);
                DoRemoteAttacks((*base_hexagon)[n]);
                if(attacker->GetHealth() <= 0){
                    map->Get((*base_hexagon)[n])->Insert(NULL);//kill.
                    delete attacker;
                }
                else{
                    will_be_created = false;
                }
            }
        }
    }
    attacker = RunTask(desire_map->GetDesire(_center), 1 - biulder_id);
    if(attacker != NULL){
        attacker->SetLocation(_center);
        map->Get(_center)->Insert(attacker);
        attacker->SetLocation(_center);
        DoRemoteAttacks(_center);
        if(attacker->GetHealth() <= 0){
            map->Get(_center)->Insert(NULL);//kill.
            delete attacker;
        }
        else{
            will_be_created = false;
        }
    }
    if(will_be_created){
        qDebug()<<"creating biulding...";
        //create biulding on map.
        biulding = RunTask(desire_map->GetDesire(_center), biulder_id);
        biulding->SetLocation(_center);
        map->Get(_center)->Insert(biulding);

        base_hexagon->clear();
        base_hexagon = map->GetHexagonsAround(_center, 1, biulding->GetRadiousOnMap());
        for(int i = 0; i < base_hexagon->size(); i++){
            if((*base_hexagon)[i].first >= 0 && (*base_hexagon)[i].first < map->Width() && (*base_hexagon)[i].second >= 0 && (*base_hexagon)[i].second < map->Height()){
                map->Get((*base_hexagon)[i])->Insert(biulding);
                map->Get((*base_hexagon)[i])->SetAsSideHexagon();
            }
        }
    }
}

void Server::DoRemoteAttacks(QPair<int, int> _location) {
    remote_attack[_location.first][_location.second] = true;
    Desire * _desire = desire_map->GetDesire(_location);
    GameObject * tmp;
    GameObject * attack;

    attack = map->Get(_location)->ObjectInside();
    if(attack != NULL){
        for (int i = 0; i < _desire->desire.size(); i++){
            if(_desire->desire[i].task_id == task_remote_attack){
                tmp = original_map->Get(_desire->desire[i].location)->ObjectInside();
                if(tmp != NULL){
                    attack->SetHealth(attack->GetHealth() - tmp->GetStamina());
                }
            }
        }
    }
}

void Server::DoExtraction(QPair<int, int> _location) {
    Desire * _desire = desire_map->GetDesire(_location);
    GameObject * worker;
    GameObject * resource;
    resource = map->Get(_location)->ObjectInside();
    if(resource != NULL){
        for (int i = 0; i < _desire->desire.size(); i++){
            if(_desire->desire[i].task_id == task_extraction){
                worker = map->Get(_desire->desire[i].location)->ObjectInside();
                if(worker != NULL){
                    resource->SetHealth(resource->GetHealth() - worker->GetStamina());
                    //add to worker sourses base on worker id.
                }
            }
        }
    }
}

void Server::DoCompleteBiulding(QPair<int, int> _location) {
    Desire * _desire = desire_map->GetDesire(_location);
    GameObject * worker;
    GameObject * biulding;
    biulding = map->Get(_location)->ObjectInside();
    if(biulding != NULL){
        for (int i = 0; i < _desire->desire.size(); i++){
            if(_desire->desire[i].task_id == task_complete_biulding){
                worker = map->Get(_desire->desire[i].location)->ObjectInside();
                if(worker != NULL){
                    biulding->SetHealth(biulding->GetHealth() + worker->GetStamina());
                }
            }
        }
    }
}
