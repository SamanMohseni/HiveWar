#include "FixedPositionObject.h"


FixedPositionObject::FixedPositionObject() {
    scene_rect_deviation = game_manager_proxy->GetSceneRectDeviation();

    QTimer *match_screen_timer = new QTimer();
    connect(match_screen_timer,SIGNAL(timeout()),this,SLOT(MatchScreen()));
    match_screen_timer->start(10);
}

void FixedPositionObject::setPos(int _x, int _y) {
    original_x = _x;
    original_y = _y;
    QGraphicsPixmapItem::setPos(original_x + scene_rect_deviation.first, original_y + scene_rect_deviation.second);
}

void FixedPositionObject::MatchScreen() {
    if(game_manager_proxy->GetSceneRectDeviation() != scene_rect_deviation){
        scene_rect_deviation = game_manager_proxy->GetSceneRectDeviation();
        QGraphicsPixmapItem::setPos(original_x + scene_rect_deviation.first, original_y + scene_rect_deviation.second);
    }
}
