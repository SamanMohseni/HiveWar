#ifndef AI_H
#define AI_H

#include "Map.h"

class AI {
public:
    AI(Map * _map);
    void Run();
private:
    Map * map;
};

#endif // AI_H
