#include "AllGameObjects.h"
#include <QDebug>
//GAMEOBJECT:


GameObject::GameObject() {
    //set health and in_task_mode.
    health = 100;
    in_task_mode = false;
    ID = 0;
    //...
    setZValue(100);
    radious_on_map = 0;
}

void GameObject::SetLocation(QPair<int, int> _location) {
    location = _location;
}
/*
void GameObject::SetLocation(Hexagon *_hexagon) {
    location = _hexagon->GetLocation();
}
*/
void GameObject::SetPosition() {
    if(location.first % 2 == 0) {
        setPos(((hexagon_width-hexagon_thickness)*3/4)*location.first+left_corner+(hexagon_width-image_width)/2, (hexagon_height-hexagon_thickness) * location.second + up_corner+(hexagon_height-image_height)/2);
    }
    else {
        setPos(((hexagon_width-hexagon_thickness)*3/4)*location.first+left_corner+(hexagon_width-image_width)/2, (hexagon_height-hexagon_thickness) * (location.second + 0.5) + up_corner+(hexagon_height-image_height)/2);
    }
}

void GameObject::SetID(int _id) {
    ID = _id;
}

void GameObject::SetHealth(int _health) {
    health = _health;
}

void GameObject::SetStamina(int _stamina) {
    stamina = _stamina;
}
/*
void GameObject::SetGameManager(GameManager *_game_manager) {
    game_manager = _game_manager;
}
*/
void GameObject::SetTask() {
    in_task_mode = 1;
}

void GameObject::MoveOnScreen(double _D_X, double _D_Y) {
    setPos(x() + _D_X, y() + _D_Y);
}

QPair<int, int> GameObject::GetLocation() {
    return location;
}

int GameObject::GetHealth() {
    return health;
}

int GameObject::GetStamina() {
    return stamina;
}

int GameObject::GetID() {
    return ID;
}

bool GameObject::IsTasked() {
    return in_task_mode;
}

void GameObject::Move(QPair<int, int>) {

}

void GameObject::Shoot(QPair<int, int>) {

}

void GameObject::RemoteAttack(QPair<int, int>) {

}

void GameObject::SetBiuldingType(OBJECT_TYPE _biulding_type) {

}

QPair<int, int> GameObject::NextLocation() {
    return location;
}

QVector<QPair<int, int> > *GameObject::GetTargets() {
    return NULL;
}

int GameObject::GetAttackRadius() {
    return 1;
}

int GameObject::GetAttackStartPoint() {
    return 1;
}

int GameObject::GetRadiousOnMap() {
    return radious_on_map;
}

QPair<int, int> GameObject::GetTarget() {
    return QPair<int, int>(-1, -1);
}

OBJECT_TYPE GameObject::GetObjectType() {
    return type_base;
}

int GameObject::GetObjectSize() {
    return sizeof(*this);
}

bool GameObject::IsTaskable() {

}

OBJECT_TYPE GameObject::BiuldingType() {

}

void GameObject::ShowMenu(QGraphicsScene *scene) {

}


void GameObject::Save(QDataStream *_out) {
    //object_type:
    OBJECT_TYPE object_type;
    object_type = GetObjectType();
    _out->writeRawData((char*)&object_type,sizeof(object_type));
    //
    //Base object data:
    //Locaton:
    int _x = location.first;
    int _y = location.second;
    _out->writeRawData((char*)&_x, sizeof(_x));
    _out->writeRawData((char*)&_y, sizeof(_y));
    //
    _out->writeRawData((char*)&health, sizeof(health));
    _out->writeRawData((char*)&stamina, sizeof(stamina));
    _out->writeRawData((char*)&ID, sizeof(ID));
    _out->writeRawData((char*)&in_task_mode, sizeof(in_task_mode));
    //
}

void GameObject::Load(QFile *_input_file) {
    //Base object data:
    //Locaton:
    int _x, _y;
    _input_file->read((char*)&_x, sizeof(_x));
    _input_file->read((char*)&_y, sizeof(_y));
    location = QPair<int, int>(_x, _y);
    //
    _input_file->read((char*)&health, sizeof(health));
    _input_file->read((char*)&stamina, sizeof(stamina));
    _input_file->read((char*)&ID, sizeof(ID));
    _input_file->read((char*)&in_task_mode, sizeof(in_task_mode));
    //
}

void GameObject::ClearDesire() {
    in_task_mode = false;
}

void GameObject::mousePressEvent(QMouseEvent *) {

}

//these might be used...
/*
QPair<int, int> GameObject::NextLocation() {
    return location;//becouse its virtual, this will work just for static objects.
}

QVector<QPair<int, int> > *GameObject::GetTargets() {
    return nullptr;
}

int GameObject::GetAttackRadius() {
    return 0;
}
.
.
.
*/
//ENDOFGAMEOBJECT..................................................................


//MOVINGOBJECT:

MovingObject::MovingObject() {
    next_location = QPair<int, int> (-1, -1);
}

void MovingObject::Move(QPair<int, int> _target) {
    next_location = _target;
}
/*
void MovingObject::Move(Hexagon *_target) {
    next_location = _target->GetLocation();
}
*/
QPair<int, int> MovingObject::NextLocation() {
    return next_location;
}

bool MovingObject::IsTaskable() {
    return true;
}

void MovingObject::Save(QDataStream *_out) {
    GameObject::Save(_out);
    //NextLocaton:
    int _x = next_location.first;
    int _y = next_location.second;
    _out->writeRawData((char*)&_x, sizeof(_x));
    _out->writeRawData((char*)&_y, sizeof(_y));
    //
}

void MovingObject::Load(QFile *_input_file) {
    GameObject::Load(_input_file);
    //Locaton:
    int _x, _y;
    _input_file->read((char*)&_x, sizeof(_x));
    _input_file->read((char*)&_y, sizeof(_y));
    next_location = QPair<int, int>(_x, _y);
    //
}

void MovingObject::ClearDesire() {
    GameObject::ClearDesire();
    next_location = QPair<int, int>(-1, -1);
}

//ENDOFMOVINGOBJECT..................................................................

//BOMBEROBJECT:

BomberObject::BomberObject() {
    targets = new QVector<QPair<int, int> >;
}

void BomberObject::ShowMenu(QGraphicsScene *scene) {
    all_buttons[BOMBERBUTTON]->setPos(left_corner, up_corner);
    scene->addItem(all_buttons[BOMBERBUTTON]);
    on_screen.push_back(all_buttons[BOMBERBUTTON]);
    all_buttons[BOMBERBUTTON]->VirtualClick();
}

void BomberObject::Shoot(QPair<int, int> _target) {
    targets->push_back(_target);
}

QVector<QPair<int, int> > *BomberObject::GetTargets() {
    return targets;
}

int BomberObject::GetAttackRadius() {
    return attack_radius;
}

int BomberObject::GetAttackStartPoint() {
    return start_point_on_map;
}

bool BomberObject::IsTaskable() {
    return true;
}

void BomberObject::Save(QDataStream *_out) {
    GameObject::Save(_out);

    _out->writeRawData((char*)&attack_radius, sizeof(attack_radius));
    //Size of vector:
    int size_of_vector = targets->size();
    _out->writeRawData((char*)&size_of_vector, sizeof(size_of_vector));
    //
    int _x, _y;
    for(int i = 0; i < size_of_vector; i++){
        //Locaton:
        _x = (*targets)[i].first;
        _y = (*targets)[i].second;
        _out->writeRawData((char*)&_x, sizeof(_x));
        _out->writeRawData((char*)&_y, sizeof(_y));
        //
    }
}

void BomberObject::Load(QFile *_input_file) {
    GameObject::Load(_input_file);

    _input_file->read((char*)&attack_radius, sizeof(attack_radius));
    //Size of vector:
    int size_of_vector;
    _input_file->read((char*)&size_of_vector, sizeof(size_of_vector));
    //
    int _x, _y;
    for(int i = 0; i < size_of_vector; i++){
        //Locaton:
        _input_file->read((char*)&_x, sizeof(_x));
        _input_file->read((char*)&_y, sizeof(_y));
        (*targets)[i] = (QPair<int, int>(_x, _y));
        //
    }
}

void BomberObject::ClearDesire() {
    GameObject::ClearDesire();
    targets->clear();
}

void BomberObject::mousePressEvent(QMouseEvent *event) {
    game_manager_proxy->Report(location);
}

//ENDOFBOMBEROBJECT..................................................................

//DEFENCETOWER:

DefenseTower::DefenseTower() {
    attack_radius = 3;
    radious_on_map = defense_tower_radious;
    start_point_on_map = 2;
    setPixmap(QPixmap(":/images/defencetower.png"));/////
    image_width = defense_tower_width;
    image_height = defense_tower_height;
    health = 1000;
    stamina = 50;
}

OBJECT_TYPE DefenseTower::GetObjectType() {
    return type_defencetower;
}

int DefenseTower::GetObjectSize() {
    return sizeof(*this);
}

void DefenseTower::Save(QDataStream *_out) {
    BomberObject::Save(_out);
}

void DefenseTower::Load(QFile *_input_file) {
    BomberObject::Load(_input_file);
}

//ENDOFDEFENCETOWER..................................................................

//DefenseTowerHalfBiuld:

DefenseTowerHalfBiuld::DefenseTowerHalfBiuld() {
    setPixmap(QPixmap(":/images/defencetowerhalf.png"));/////
    image_width = defense_tower_width;
    image_height = defense_tower_height;
    health = 1;//one percent.
    radious_on_map = defense_tower_radious;
}

OBJECT_TYPE DefenseTowerHalfBiuld::GetObjectType() {
    return type_defencetower_halfbiuld;
}

int DefenseTowerHalfBiuld::GetObjectSize() {
    return sizeof(*this);
}

void DefenseTowerHalfBiuld::Save(QDataStream *_out) {
    GameObject::Save(_out);
}

void DefenseTowerHalfBiuld::Load(QFile *_input_file) {
    GameObject::Load(_input_file);
}

//ENDOFDEFENCETOWERHALFBIULD.........................................................

//CASTLE:

Castle::Castle() {
    attack_radius = 6;
    radious_on_map = castle_radious;
    start_point_on_map = 4;
    setPixmap(QPixmap(":/images/castle.png"));/////
    image_width = castle_width;
    image_height = castle_height;
    health = 2000;
    stamina = 50;
}

OBJECT_TYPE Castle::GetObjectType() {
    return type_castle;
}

int Castle::GetObjectSize() {
    return sizeof(*this);
}

void Castle::Save(QDataStream *_out) {
    BomberObject::Save(_out);
}

void Castle::Load(QFile *_input_file) {
    BomberObject::Load(_input_file);
}

//ENDOFCASTLE........................................................................

//CASTLEHALFBIULD:

CastleHalfBiuld::CastleHalfBiuld() {
    setPixmap(QPixmap(":/images/castlehalf.png"));/////
    image_width = castle_width;
    image_height = castle_height;
    health = 1;//one percent.
    radious_on_map = castle_radious;
}

OBJECT_TYPE CastleHalfBiuld::GetObjectType() {
    return type_castle_halfbiuld;
}

int CastleHalfBiuld::GetObjectSize() {
    return sizeof(*this);
}

void CastleHalfBiuld::Save(QDataStream *_out) {
    GameObject::Save(_out);
}

void CastleHalfBiuld::Load(QFile *_input_file) {
    GameObject::Load(_input_file);
}

//ENDOFCASTLEHALFBIULD...............................................................

//HOVEL:

Hovel::Hovel() {
    attack_radius = 4;
    radious_on_map = hovel_radious;
    start_point_on_map = 3;
    setPixmap(QPixmap(":/images/hovel.png"));/////
    image_width = hovel_width;
    image_height = hovel_height;
    health = 200;
}

void Hovel::ShowMenu(QGraphicsScene *scene) {
    all_buttons[CREATEWORKERBUTTON]->setPos(left_corner, up_corner);
    scene->addItem(all_buttons[CREATEWORKERBUTTON]);
    on_screen.push_back(all_buttons[CREATEWORKERBUTTON]);
    all_buttons[CREATEWORKERBUTTON]->VirtualClick();
}

OBJECT_TYPE Hovel::GetObjectType() {
    return type_hovel;
}

int Hovel::GetObjectSize() {
    return sizeof(*this);
}

void Hovel::Save(QDataStream *_out) {
    BomberObject::Save(_out);
}

void Hovel::Load(QFile *_input_file) {
    BomberObject::Load(_input_file);
}

//ENDOFHOVEL.........................................................................

//HOVELHALFBIULD:

HovelHalfBiuld::HovelHalfBiuld() {
    setPixmap(QPixmap(":/images/hovelhalf.png"));/////
    image_width = hovel_width;
    image_height = hovel_height;
    health = 1;//one percent.
    radious_on_map = hovel_radious;
}

OBJECT_TYPE HovelHalfBiuld::GetObjectType() {
    return type_hovel_halfbiuld;
}

int HovelHalfBiuld::GetObjectSize() {
    return sizeof(*this);
}

void HovelHalfBiuld::Save(QDataStream *_out) {
    GameObject::Save(_out);
}

void HovelHalfBiuld::Load(QFile *_input_file) {
    GameObject::Load(_input_file);
}

//ENDOFHOVELHALFBIULD................................................................

//MILITARYHOME:

MilitaryHome::MilitaryHome() {
    attack_radius = 4;
    radious_on_map = militaryhome_radious;
    start_point_on_map = 3;
    setPixmap(QPixmap(":/images/military_home.png"));/////
    image_width = militaryhome_width;
    image_height = militaryhome_height;
    health = 300;
}

void MilitaryHome::ShowMenu(QGraphicsScene *scene) {
    all_buttons[CREATESOLDIERBUTTON]->setPos(left_corner, up_corner);
    scene->addItem(all_buttons[CREATESOLDIERBUTTON]);
    on_screen.push_back(all_buttons[CREATESOLDIERBUTTON]);
    all_buttons[CREATESOLDIERBUTTON]->VirtualClick();
}

OBJECT_TYPE MilitaryHome::GetObjectType() {
    return type_military_home;
}

int MilitaryHome::GetObjectSize() {
    return sizeof(*this);
}

void MilitaryHome::Save(QDataStream *_out) {
    BomberObject::Save(_out);
}

void MilitaryHome::Load(QFile *_input_file) {
    BomberObject::Load(_input_file);
}

//ENDOFMILITARYHOME...................................................................

//MILITARYHOMEHALFBIULD:

MilitaryHomeHalfBiuld::MilitaryHomeHalfBiuld() {
    setPixmap(QPixmap(":/images/military_homehalf.png"));/////
    image_width = militaryhome_width;
    image_height = militaryhome_height;
    health = 1;//one percent.
    radious_on_map = militaryhome_radious;
}

OBJECT_TYPE MilitaryHomeHalfBiuld::GetObjectType() {
    return type_military_home_halfbiuld;
}

int MilitaryHomeHalfBiuld::GetObjectSize() {
    return sizeof(*this);
}

void MilitaryHomeHalfBiuld::Save(QDataStream *_out) {
    GameObject::Save(_out);
}

void MilitaryHomeHalfBiuld::Load(QFile *_input_file) {
    GameObject::Load(_input_file);
}

//ENDOFMILITARYHOMEHALFBIULD..........................................................

//SOLDIER:

Soldier::Soldier() {
    setPixmap(QPixmap(":/images/soldier.png"));/////
    image_width = soldier_width;
    image_height = soldier_height;
    attack_radius = 1;
    remote_attack = QPair<int, int> (-1, -1);
    health = 150;
    stamina = 50;
}

void Soldier::ShowMenu(QGraphicsScene *scene) {
    all_buttons[MOVEBUTTON]->setPos(left_corner, up_corner);
    scene->addItem(all_buttons[MOVEBUTTON]);
    on_screen.push_back(all_buttons[MOVEBUTTON]);

    all_buttons[REMOTEATTACKBUTTON]->setPos(left_corner, up_corner + menu_button_size * 1.5);
    scene->addItem(all_buttons[REMOTEATTACKBUTTON]);
    on_screen.push_back(all_buttons[REMOTEATTACKBUTTON]);

    all_buttons[MOVEBUTTON]->VirtualClick();
}

void Soldier::RemoteAttack(QPair<int, int> _remote_attack) {
    remote_attack = _remote_attack;
}
/*
void Soldier::RemoteAttack(Hexagon *_remote_attack) {
    remote_attack = _remote_attack->GetLocation();
}
*/
int Soldier::GetAttackRadius() {
    return attack_radius;
}

QPair<int, int> Soldier::GetTarget() {
    return remote_attack;
}

OBJECT_TYPE Soldier::GetObjectType() {
    return type_soldier;
}

int Soldier::GetObjectSize() {
    return sizeof(*this);
}

void Soldier::Save(QDataStream *_out) {
    MovingObject::Save(_out);

    _out->writeRawData((char*)&attack_radius, sizeof(attack_radius));

    //Locaton:
    int _x = remote_attack.first;
    int _y = remote_attack.second;
    _out->writeRawData((char*)&_x, sizeof(_x));
    _out->writeRawData((char*)&_y, sizeof(_y));
    //
}

void Soldier::Load(QFile *_input_file) {
    MovingObject::Load(_input_file);

    _input_file->read((char*)&attack_radius, sizeof(attack_radius));

    //Locaton:
    int _x, _y;
    _input_file->read((char*)&_x, sizeof(_x));
    _input_file->read((char*)&_y, sizeof(_y));
    remote_attack = QPair<int, int>(_x, _y);
    //
}

void Soldier::ClearDesire() {
    MovingObject::ClearDesire();
    remote_attack = QPair<int, int> (-1, -1);
}

void Soldier::mousePressEvent(QMouseEvent *event) {
    game_manager_proxy->Report(location);
}

//ENDOFSOLDIER....................................................................

//Worker:

Worker::Worker() {
    setPixmap(QPixmap(":/images/worker.png"));/////
    image_width = worker_width;
    image_height = worker_height;
    attack_radius = 2;
    remote_attack = QPair<int, int> (-1, -1);
    biulding_type = type_none;
    health = 100;
    stamina = 25;
}

void Worker::ShowMenu(QGraphicsScene *scene) {
    all_buttons[MOVEBUTTON]->setPos(left_corner, up_corner);
    scene->addItem(all_buttons[MOVEBUTTON]);
    on_screen.push_back(all_buttons[MOVEBUTTON]);

    all_buttons[CREATEHOVELBUTTON]->setPos(left_corner, up_corner + menu_button_size * 1.5);
    scene->addItem(all_buttons[CREATEHOVELBUTTON]);
    on_screen.push_back(all_buttons[CREATEHOVELBUTTON]);

    all_buttons[CREATEMILITARYHOUSEBUTTON]->setPos(left_corner, up_corner + menu_button_size * 3);
    scene->addItem(all_buttons[CREATEMILITARYHOUSEBUTTON]);
    on_screen.push_back(all_buttons[CREATEMILITARYHOUSEBUTTON]);

    all_buttons[CREATEDEFENCETOWERBUTTON]->setPos(left_corner, up_corner + menu_button_size * 4.5);
    scene->addItem(all_buttons[CREATEDEFENCETOWERBUTTON]);
    on_screen.push_back(all_buttons[CREATEDEFENCETOWERBUTTON]);

    all_buttons[CREATECASTLEBUTTON]->setPos(left_corner, up_corner + menu_button_size * 6);
    scene->addItem(all_buttons[CREATECASTLEBUTTON]);
    on_screen.push_back(all_buttons[CREATECASTLEBUTTON]);

    all_buttons[EXTRACTIONBUTTON]->setPos(left_corner, up_corner + menu_button_size * 7.5);
    scene->addItem(all_buttons[EXTRACTIONBUTTON]);
    on_screen.push_back(all_buttons[EXTRACTIONBUTTON]);

    all_buttons[COMPLETEBIULDING]->setPos(left_corner, up_corner + menu_button_size * 9);
    scene->addItem(all_buttons[COMPLETEBIULDING]);
    on_screen.push_back(all_buttons[COMPLETEBIULDING]);

    all_buttons[MOVEBUTTON]->VirtualClick();
}

void Worker::SetBiuldingType(OBJECT_TYPE _biulding_type) {
    biulding_type = _biulding_type;
}

OBJECT_TYPE Worker::BiuldingType() {
    return biulding_type;
}

OBJECT_TYPE Worker::GetObjectType() {
    return type_worker;
}

int Worker::GetObjectSize() {
    return sizeof(*this);
}

void Worker::Save(QDataStream *_out) {
    Soldier::Save(_out);
    _out->writeRawData((char*)&biulding_type, sizeof(biulding_type));
}

void Worker::Load(QFile *_input_file) {
    Soldier::Load(_input_file);
    _input_file->read((char*)&biulding_type, sizeof(biulding_type));
}

void Worker::ClearDesire() {
    Soldier::ClearDesire();
    biulding_type = type_none;
}

//ENDOFWORKER.....................................................................

//WOOD:

Wood::Wood() {
    setPixmap(QPixmap(":/images/wood.png"));/////
    image_width = tree_width;
    image_height = tree_height;
    setZValue(101);
    health = 100;
    stamina = 10;
}

OBJECT_TYPE Wood::GetObjectType() {
    return type_wood;
}

int Wood::GetObjectSize() {
    return sizeof(*this);
}

bool Wood::IsTaskable() {
    return false;
}


//ENDOFWOOD.......................................................................

//STONE:
Stone::Stone() {
    setPixmap(QPixmap(":/images/stone.png"));/////
    image_width = stone_width;
    image_height = stone_height;
    health = 100;
    stamina = 5;
}

OBJECT_TYPE Stone::GetObjectType() {
    return type_stone;
}

int Stone::GetObjectSize() {
    return sizeof(*this);
}

bool Stone::IsTaskable() {
    return false;
}

//ENDOFSTONE......................................................................
