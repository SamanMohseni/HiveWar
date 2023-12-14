#include "DesireMap.h"


DesireMap::DesireMap(int _width, int _height) {
    width = _width;
    height = _height;
    SizeAllocate();
}

Desire *DesireMap::GetDesire(int _width, int _height) {
    return desire_map[_width][_height];
}

Desire *DesireMap::GetDesire(QPair<int, int> location) {
    return desire_map[location.first][location.second];
}

void DesireMap::Clear() {
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            desire_map[i][j]->desire.clear();
        }
    }
}

void DesireMap::SizeAllocate() {
    desire_map = new Desire * *[width];
    for (int i = 0; i < width; i++){
        desire_map[i] = new Desire * [height];
        for(int j = 0; j < height; j++){
            desire_map[i][j] = new Desire;
            desire_map[i][j]->desire.clear();
        }
    }
}
