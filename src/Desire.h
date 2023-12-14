#ifndef DESIRE_H
#define DESIRE_H

#include <QVector>
#include <QPair>

enum TaskID {task_move, task_remote_attack, task_create_people, task_create_soldier, task_extraction,
            task_biuld_hovel, task_biuld_military_house, task_biuld_defence_tower, task_biuld_castle,
            task_complete_biulding, task_biuld};

struct Request {
    int ID;//id might be useless due to servers access to map.
    TaskID task_id;
    QPair<int, int> location;
};

struct Desire {
    QVector <Request> desire;//QPair<int, int> is tasker location.
    //vector is filled sorted by ID.
};

#endif // DESIRE_H
