#ifndef BUTTONS_H
#define BUTTONS_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <QObject>
#include <QVector>

#include "GameManagerProxy.h"
#include "FixedPositionObject.h"
//#include "GameManager.h"
extern GameManagerProxy * game_manager_proxy;

//extern QVector <Button *> on_screen;

#define MOVEBUTTON 1
#define REMOTEATTACKBUTTON 2
#define BOMBERBUTTON 3
#define EXTRACTIONBUTTON 4

#define CREATEWORKERBUTTON 5
#define CREATESOLDIERBUTTON 6
#define CREATEDEFENCETOWERBUTTON 7
#define CREATECASTLEBUTTON 8
#define CREATEHOVELBUTTON 9
#define CREATEMILITARYHOUSEBUTTON 10
#define COMPLETEBIULDING 11
#define CREATEWOODBUTTON 12
#define CREATESTONEBUTTON 13

#define SAVEBUTTON 14

class Button : public FixedPositionObject {
    Q_OBJECT
public:
    Button();
    int GetButtonID();
    //static QVector <Button *> all_buttons;
    void Reset();
    void VirtualClick();
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
protected:
    int button_id;
    QString image_directory;
    QString clicked_image_directory;
};
//=====================================================================

extern Button * *all_buttons;

//=====================================================================

//MoveButton:
class MoveButton : public Button {
public:
    MoveButton();//set icon. set id.
};
//=====================================================================

//RemoteAttackButton:
class RemoteAttackButton : public Button {
public:
    RemoteAttackButton();//set icon. set id.
};
//=====================================================================

//BomberButton:
class BomberButton : public Button {
public:
    BomberButton();//set icon. set id.
};
//=====================================================================

//ExtractionButton:
class ExtractionButton : public Button {
public:
    ExtractionButton();//set icon. set id.
};
//=====================================================================

//CreateWorkerButton:
class CreateWorkerButton : public Button {
public:
    CreateWorkerButton();//set icon. set id.
};

//=====================================================================

//SoldierButton:
class CreateSoldierButton : public Button {
public:
    CreateSoldierButton();//set icon. set id.
};
//=====================================================================

//DefenceTowerButton:
class CreateDefenceTowerButton : public Button {
public:
    CreateDefenceTowerButton();//set icon. set id.saveicon
};
//=====================================================================

//CastleButton:
class CreateCastleButton : public Button {
public:
    CreateCastleButton();//set icon. set id.saveicon
};
//=====================================================================

//HovelButton:
class CreateHovelButton : public Button {
public:
    CreateHovelButton();//set icon. set id.saveicon
};
//=====================================================================

//MilitaryHouseButton:
class CreateMilitaryHouseButton : public Button {
public:
    CreateMilitaryHouseButton();//set icon. set id.saveicon
};

//=====================================================================

//WoodButton:
class CreateWoodButton : public Button {
public:
    CreateWoodButton();//set icon. set id.
};
//=====================================================================

//StoneButton:
class CreateStoneButton : public Button {
public:
    CreateStoneButton();//set icon. set id.
};
//=====================================================================

//CompleteBiuldinButton:
class CompleteBiuldinButton : public Button {
public:
    CompleteBiuldinButton();//set icon. set id.
};

//=====================================================================

//SaveButton:

class SaveButton : public Button {
public:
    SaveButton();//set icon. set id.
};
//=====================================================================

#endif // BUTTONS_H
