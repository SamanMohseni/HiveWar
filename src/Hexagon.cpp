#include "Hexagon.h"

Hexagon::Hexagon(){
    setPixmap(QPixmap(":/images/Hexagon.png"));
    game_object = NULL;
    comming_item = NULL;
    is_comming = false;
    is_highlighted = false;
    item_has_left = false;
    is_centeral = true;
    //setScale(2);
}

void Hexagon::SetLocation(QPair<int, int> _location) {
    location = _location;
}

QPair<int, int> Hexagon::GetLocation() {
    return location;
}

void Hexagon::Insert(GameObject *_game_object){
    game_object = _game_object;
}

void Hexagon::Reserve(GameObject *_comming_item){
    comming_item = _comming_item;
    is_comming = 1;
}

void Hexagon::SetPosition() {
    if(location.first % 2 == 0) {
        setPos(((hexagon_width-hexagon_thickness)*3/4)*location.first + left_corner, (hexagon_height-hexagon_thickness) * location.second + up_corner);
    }
    else {
        setPos(((hexagon_width-hexagon_thickness)*3/4)*location.first + left_corner, (hexagon_height-hexagon_thickness) * (location.second + 0.5) + up_corner);
    }
}

void Hexagon::MoveOnScreen(double _D_X, double _D_Y) {
    setPos(x() + _D_X, y() + _D_Y);
}

void Hexagon::Highlight() {
    setPixmap(QPixmap(":/images/highlightedhexagon.png"));
    is_highlighted = true;
}

void Hexagon::EraseHighlight() {
    setPixmap(QPixmap(":/images/Hexagon.png"));
    is_highlighted = false;
}

void Hexagon::ItemIsLeaving() {
    item_has_left = true;
}

void Hexagon::SetAsSideHexagon() {
    is_centeral = false;
}

void Hexagon::SetAsCenteral() {
    is_centeral = true;
}

GameObject *Hexagon::ObjectInside(){
    return game_object;
}

GameObject *Hexagon::CommingObject(){
    return comming_item;
}

bool Hexagon::IsCenteral() {
    return is_centeral;
}

bool Hexagon::IsComming() {
    return is_comming;
}

bool Hexagon::IsHighlighted() {
    return is_highlighted;
}

bool Hexagon::ItemHasLeft() {
    return item_has_left;
}

void Hexagon::Clear() {
    is_comming = false;
    is_highlighted = false;
    item_has_left = false;
    comming_item = NULL;
}

void Hexagon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    game_manager_proxy->Report(location);
}
