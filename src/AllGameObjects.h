#ifndef ALLGAMEOBJECTS_H
#define ALLGAMEOBJECTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDataStream>
#include <QMouseEvent>
#include <QObject>
#include <QVector>
#include <math.h>
#include <QFile>
#include <QPair>

#include "GameManagerProxy.h"
#include "SystemInfo.h"
#include "Buttons.h"

extern GameManagerProxy * game_manager_proxy;

extern QVector <Button *> on_screen;
extern Button * *all_buttons;

enum OBJECT_TYPE {type_soldier, type_worker, type_defencetower, type_castle, type_hovel, type_military_home,
                  type_wood, type_stone, type_defencetower_halfbiuld, type_castle_halfbiuld, type_hovel_halfbiuld,
                  type_military_home_halfbiuld, type_biulding, type_base, type_none};

////////////////////////////////////////////////////////////////////////////
/// \brief The GameObject class
///
class GameObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    GameObject();//set health and in_task_mode.

    //SET:
    void SetLocation(QPair <int, int> _location);//we have to have satic location for file saving.
    //void SetLocation(Hexagon * _hexagon);//
    void SetPosition();//sets geomatical position based on hexagon index(locatin).
    void SetID(int _id);
    void SetHealth(int _health);
    void SetStamina(int _stamina);
    //void SetGameManager(GameManager * _game_manager);
    void SetTask();

    void MoveOnScreen(double _D_X, double _D_Y);

    //GET:
    QPair <int, int> GetLocation();//
    int GetHealth();
    int GetStamina();
    int GetID();
    bool IsTasked();

    //VIRTUAL SET:
    virtual void Move(QPair <int, int>);//set next location.
    //virtual void Move(Hexagon *);//set next location.
    virtual void Shoot(QPair <int, int>);//set target.
    //virtual void Shoot(Hexagon *);//set target.
    virtual void RemoteAttack(QPair <int, int>);//sets remote_attack
    //virtual void RemoteAttack(Hexagon *);//sets remote_attack
    virtual void SetBiuldingType(OBJECT_TYPE _biulding_type);//this is for worker

    //VIRTUAL GET:
    virtual QPair <int, int> NextLocation();
    virtual QVector<QPair<int, int> > *GetTargets();
    virtual int GetAttackRadius();
    virtual int GetAttackStartPoint();
    virtual int GetRadiousOnMap();
    virtual QPair <int, int> GetTarget();
    virtual OBJECT_TYPE GetObjectType();
    virtual int GetObjectSize();
    virtual bool IsTaskable();
    virtual OBJECT_TYPE BiuldingType();//this is for worker

    virtual void ShowMenu(QGraphicsScene * scene);//gets the scene from GameManager out of function: "Suspend".

    //virtual QVector <Hexagon *> * InAccessArea(ButtonID * button_id = nullptr);//if no button was chosen the class will automaticaly find one.

    //Saves its self:
    virtual void Save(QDataStream * _out);

    //Loads its self:
    virtual void Load(QFile * _input_file);

    virtual void ClearDesire();

public slots:
    virtual void mousePressEvent(QMouseEvent *);//gets suspended.//if in task mode report base hexagon.

protected:
    QPair <int, int> location;
    int health;//0 to 100//also is amount persentage.
    int stamina;//const//health * stamina := pure amount.
    int ID;
    bool in_task_mode;
    int image_width, image_height;
    int radious_on_map;
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The MovingObject class
///

class MovingObject : public GameObject {//data needs to be send.
public:
    MovingObject();

    void Move(QPair <int, int> _target);//sets next_location.
    //void Move(Hexagon * _target);//sets next_location.

    QPair <int, int> NextLocation();

    bool IsTaskable();

    //Saves its self:
    virtual void Save(QDataStream * _out);

    //Loads its self:
    virtual void Load(QFile * _input_file);

    virtual void ClearDesire();

protected:
    QPair <int, int> next_location;
};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The BomberObject class
///
///
class BomberObject : public GameObject {//BomberObject can be any object which can put a specific type of task to hexagons around.
    Q_OBJECT
public:
    BomberObject();

    virtual void ShowMenu(QGraphicsScene * scene);

    void Shoot(QPair <int, int> _target);//adds QPair to target.
    //void Shoot(Hexagon * target);//adds QPair to target.

    QVector<QPair<int, int> > *GetTargets();

    int GetAttackRadius();
    int GetAttackStartPoint();

    bool IsTaskable();

    //Saves its self:
    virtual void Save(QDataStream * _out);

    //Loads its self:
    virtual void Load(QFile * _input_file);

    virtual void ClearDesire();
public slots:
    virtual void mousePressEvent(QMouseEvent *event);//gets suspended.//if in task mode report base hexagon.

protected:
    int start_point_on_map;
    int attack_radius;//const
    QVector<QPair<int, int> > *targets;
};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The DefenseTower class
///
///
class DefenseTower : public BomberObject {
    Q_OBJECT
public:
    DefenseTower();//the picture must be set here.

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);

};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The DefenseTowerHalfBiuld class
///
///
class DefenseTowerHalfBiuld : public GameObject {
    Q_OBJECT
public:
    DefenseTowerHalfBiuld();//health shows progress.

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Castle class
///
///
class Castle : public BomberObject{
    Q_OBJECT
public:
    Castle();

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);

};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CastleHalfBiuld class
///
///
class CastleHalfBiuld : public GameObject {
    Q_OBJECT
public:
    CastleHalfBiuld();//health shows progress.

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Hovel class
///
///
class Hovel : public BomberObject{
    Q_OBJECT
public:
    Hovel();

    void ShowMenu(QGraphicsScene * scene);

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The HovelHalfBiuld class
///
///
class HovelHalfBiuld : public GameObject {
    Q_OBJECT
public:
    HovelHalfBiuld();//health shows progress.

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The MilitaryHome class
///
///
class MilitaryHome : public BomberObject{
    Q_OBJECT
public:
    MilitaryHome();

    void ShowMenu(QGraphicsScene * scene);

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The MilitaryHomeHalfBiuld class
///
///
class MilitaryHomeHalfBiuld : public GameObject {
    Q_OBJECT
public:
    MilitaryHomeHalfBiuld();//health shows progress.

    OBJECT_TYPE GetObjectType();//this is a virtual function.
    int GetObjectSize();//this is a virtual function.

    void Save(QDataStream * _out);
    void Load(QFile * _input_file);
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Soldier class
///
///
class Soldier : public MovingObject {
    Q_OBJECT
public:
    Soldier();//the picture must be set here.

    virtual void ShowMenu(QGraphicsScene * scene);

    void RemoteAttack(QPair <int, int> _remote_attack);//sets remote_attack
    //void RemoteAttack(Hexagon * _remote_attack);//sets remote_attack

    int GetAttackRadius();
    QPair <int, int> GetTarget();

    virtual OBJECT_TYPE GetObjectType();//

    virtual int GetObjectSize();//

    //Saves its self:
    virtual void Save(QDataStream * _out);

    //Loads its self:
    virtual void Load(QFile * _input_file);

    virtual void ClearDesire();

public slots:
    virtual void mousePressEvent(QMouseEvent * event);//gets suspended.//if in task mode report base hexagon.

protected:
    int attack_radius;//const
    QPair <int, int> remote_attack;//biuld in worker.
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Worker class
///
///
class Worker : public Soldier {
    Q_OBJECT
public:
    Worker();
    void ShowMenu(QGraphicsScene * scene);

    void SetBiuldingType(OBJECT_TYPE _biulding_type);
    OBJECT_TYPE BiuldingType();

    OBJECT_TYPE GetObjectType();//
    int GetObjectSize();//

    virtual void Save(QDataStream * _out);
    virtual void Load(QFile * _input_file);

    void ClearDesire();
private:
    OBJECT_TYPE biulding_type;
};

///////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Wood class
///
///
class Wood : public GameObject {
public:
    Wood();//the picture must be set here.

    OBJECT_TYPE GetObjectType();
    int GetObjectSize();

    bool IsTaskable();

};

///////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Stone class
///
///
class Stone : public GameObject {
public:
    Stone();//the picture must be set here.

    OBJECT_TYPE GetObjectType();
    int GetObjectSize();

    bool IsTaskable();

};

#endif // ALLGAMEOBJECTS_H
