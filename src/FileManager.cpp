#include "FileManager.h"
#include <QDebug>
FileManager::FileManager() {
    raw_data.clear();
    map = NULL;
}

Map * FileManager::LoadData(QString _location) {

    int map_width, map_height;
    OBJECT_TYPE object_type;
    GameObject * tmp;

    QFile input_file(_location);

    input_file.open(QIODevice::ReadOnly);

    input_file.read((char*)&map_width, sizeof(int));
    input_file.read((char*)&map_height, sizeof(int));

    map = new Map(map_width, map_height);

    qDebug()<<"map created!";
    while (!input_file.atEnd()){
        input_file.read((char*)&object_type, sizeof(object_type));

        switch (object_type){
        case type_worker:
            tmp = new Worker();
            break;
        case type_soldier:
            tmp = new Soldier();
            break;
        case type_defencetower:
            tmp = new DefenseTower();
            break;
        case type_defencetower_halfbiuld:
            tmp = new DefenseTowerHalfBiuld();
            break;
        case type_castle:
            tmp = new Castle();
            break;
        case type_castle_halfbiuld:
            tmp = new CastleHalfBiuld();
            break;
        case type_hovel:
            tmp = new Hovel();
            break;
        case type_hovel_halfbiuld:
            tmp = new HovelHalfBiuld();
            break;
        case type_military_home:
            tmp = new MilitaryHome();
            break;
        case type_military_home_halfbiuld:
            tmp = new MilitaryHomeHalfBiuld();
            break;
        case type_wood:
            tmp = new Wood();
            break;
        case type_stone:
            tmp = new Stone();
            break;
        default:
            qDebug()<<"error!";
        }
        tmp->Load(&input_file);
        map->Get(tmp->GetLocation())->Insert(tmp);//add object pointer to hexagon.

        QVector<QPair<int, int> > *base_hexagon;
        base_hexagon = map->GetHexagonsAround(tmp->GetLocation(), 1, tmp->GetRadiousOnMap());
        qDebug()<<base_hexagon->size();
        for(int i = 0; i < base_hexagon->size(); i++){
            if((*base_hexagon)[i].first >= 0 && (*base_hexagon)[i].first < map->Width() && (*base_hexagon)[i].second >= 0 && (*base_hexagon)[i].second < map->Height()){
                map->Get((*base_hexagon)[i])->Insert(tmp);
                map->Get((*base_hexagon)[i])->SetAsSideHexagon();
            }
        }
    }
    return map;
}

void FileManager::WriteData(Map *map, QString _location) {
    CreateRawData(map);
    QFile output_file(_location);
    output_file.open(QIODevice::WriteOnly);
    output_file.write(raw_data);
    output_file.close();
}

void FileManager::CreateRawData(Map *map) {
    QDataStream out(&raw_data,QIODevice::WriteOnly);
    int width, height;

    width = map->Width();
    height = map->Height();
    out.writeRawData((char*)&width, sizeof(int));
    out.writeRawData((char*)&height, sizeof(int));

    for(int i = 0; i < map->Width(); i++){
        for(int j = 0; j< map->Height(); j++){
            if(map->Get(i, j)->ObjectInside() != NULL && map->Get(i, j)->IsCenteral()){
                map->Get(i, j)->ObjectInside()->Save(&out);
            }
        }
    }
}
