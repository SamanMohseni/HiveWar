#ifndef DESIREMAP_H
#define DESIREMAP_H

#include <QPair>

#include "Desire.h"

class DesireMap {
public:
    DesireMap(int _width, int _height);
    Desire *GetDesire(int _width, int _height);
    Desire *GetDesire(QPair<int, int> location);
    void Clear();
    //void Insert(Desire * _desire, int _width, int _height);
private:
    void SizeAllocate();
private:
    Desire * ** desire_map;
    int width, height;
};

#endif // DESIREMAP_H
