#include "AI.h"
#include <QDebug>

AI::AI(Map *_map) {
    map = _map;
    //...
}

void AI::Run() {//Random AI.
    qDebug()<<"AI RUNNING...";
    GameObject * tmp;
    QVector<QPair<int, int> > *base_hexagon;
    QVector<QPair<int, int> > attackable;
    QPair<int, int> location;
    int random_number, random_number1;

    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j < map->Height(); j++){
            location = QPair<int, int>(i, j);
            tmp = map->Get(location)->ObjectInside();

            if(tmp != NULL && tmp->GetID() == 1){
                base_hexagon = map->GetHexagonsAround(location, 1, tmp->GetAttackRadius());
                attackable.clear();
                for(int n = 0; n < base_hexagon->size(); n++){
                    if((*base_hexagon)[n].first >= 0 && (*base_hexagon)[n].first < map->Width() && (*base_hexagon)[n].second >= 0 && (*base_hexagon)[n].second < map->Height()){
                        if(map->Get((*base_hexagon)[n])->ObjectInside() == NULL && !map->Get((*base_hexagon)[n])->IsComming()){
                            attackable.push_back((*base_hexagon)[n]);
                        }
                    }
                }
                if(tmp->GetObjectType() == type_soldier || tmp->GetObjectType() == type_worker){
                    if(attackable.size() > 0){
                        random_number = qrand() % (attackable.size());
                        tmp->Move(attackable[random_number]);
                        map->Get(tmp->GetLocation())->ItemIsLeaving();
                        map->Get(attackable[random_number])->Reserve(tmp);
                    }
                }
                else if(tmp->GetObjectType() == type_defencetower || tmp->GetObjectType() == type_hovel || tmp->GetObjectType() == type_military_home){
                    if(attackable.size() > 0){
                        random_number = qrand() % (attackable.size());
                        tmp->RemoteAttack(attackable[random_number]);
                    }
                }
            }
        }
    }
    qDebug()<<"AI DONE!";
    //do sth...
}
