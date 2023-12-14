#include "Map.h"

Map::Map(int _width, int _height){
    width = _width;
    height = _height;
    SizeAllocate();
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            map[i][j] = new Hexagon();
            Get(i, j)->SetLocation(QPair<int, int>(i, j));
        }
    }
    move_structure[0][0]=-1; move_structure[0][1]= 1;
    move_structure[1][0]= 0; move_structure[1][1]= 1;
    move_structure[2][0]= 1; move_structure[2][1]= 1;
    move_structure[3][0]= 1; move_structure[3][1]=-1;
    move_structure[4][0]= 0; move_structure[4][1]=-1;
    move_structure[5][0]=-1; move_structure[5][1]=-1;
}

Hexagon *Map::Get(int x, int y){
    return map[x][y];
}

Hexagon *Map::Get(QPair<int, int> _location){
    return map[_location.first][_location.second];
}

QVector<QPair<int, int> > *Map::GetHexagonsAround(QPair<int, int> _location, int _from_radious, int _untill_radious) {
    neighbours.clear();
    int structure_number, counter;
    int center_x, center_y;
    int previous_x, previous_y;
    int s_x, s_y;
    bool Parity;

    center_x = _location.first;
    center_y = _location.second;

    for(int r = _from_radious, max_r = _untill_radious; r <= max_r; r++){
        neighbours.push_back(QPair<int, int>(center_x, center_y - r));
        structure_number = 0;
        s_x = move_structure[structure_number][0];
        s_y = move_structure[structure_number][1];

        counter = 0;
        while(true){
            previous_x = neighbours.last().first;
            previous_y = neighbours.last().second;
            Parity = previous_x%2;

            if(structure_number == 5 && counter == r-1){
                break;//end of loop.
            }

            if(s_x == 0){
                neighbours.push_back(QPair<int, int>(previous_x + s_x, previous_y + s_y));
            }
            else if(s_y == 1){
                neighbours.push_back(QPair<int, int>(previous_x + s_x, previous_y + Parity));
            }
            else{
                neighbours.push_back(QPair<int, int>(previous_x + s_x, previous_y - !Parity));
            }

            counter++;

            if(counter == r){
                structure_number++;
                s_x = move_structure[structure_number][0];
                s_y = move_structure[structure_number][1];
                counter = 0;
            }
        }
    }
    return &neighbours;
}

void Map::InsertObjectsAround(GameObject * _game_object, QPair<int, int> _location, int _from_radious, int _untill_radious) {
    GetHexagonsAround(_location, _from_radious, _untill_radious);
    for(int i = 0; i < neighbours.size(); i++){
        if(neighbours[i].first >= 0 && neighbours[i].first < Width() && neighbours[i].second >= 0 && neighbours[i].second < Height()){
            Get(neighbours[i])->Insert(_game_object);
            Get(neighbours[i])->SetAsSideHexagon();
        }
    }
}

void Map::RemoveObjectsAround(QPair<int, int> _location, int _from_radious, int _untill_radious) {
    GetHexagonsAround(_location, _from_radious, _untill_radious);
    for(int i = 0; i < neighbours.size(); i++){
        if(neighbours[i].first >= 0 && neighbours[i].first < Width() && neighbours[i].second >= 0 && neighbours[i].second < Height()){
            Get(neighbours[i])->Insert(NULL);
            Get(neighbours[i])->SetAsCenteral();
        }
    }
}

void Map::Draw(QGraphicsScene *_scene){
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            map[i][j]->SetPosition();
            _scene->addItem(map[i][j]);
            if(map[i][j]->ObjectInside() != NULL && map[i][j]->IsCenteral()){
                map[i][j]->ObjectInside()->SetPosition();
                _scene->addItem(map[i][j]->ObjectInside());
            }
        }
    }
}

void Map::Clear(QGraphicsScene *_scene) {
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if(map[i][j]->ObjectInside() != NULL && map[i][j]->IsCenteral()){
                _scene->removeItem(map[i][j]->ObjectInside());
            }
            _scene->removeItem(map[i][j]);
        }
    }
}

void Map::DrawOneItem(QPair<int, int> _location, QGraphicsScene *_scene) {
    int i = _location.first;
    int j = _location.second;
    if(map[i][j]->ObjectInside() != NULL){
        map[i][j]->ObjectInside()->SetPosition();
        _scene->addItem(map[i][j]->ObjectInside());
    }
}

int Map::Width() {
    return width;
}

int Map::Height() {
    return height;
}

void Map::SizeAllocate(){
    map = new Hexagon * *[width];
    for (int i = 0; i < width; i++){
        map[i] = new Hexagon * [height];
    }
}

