#include "Buttons.h"
#include <QDebug>
///////////////////////////////////////////////////////////////////////////
/// \brief Button::Button
///
///
Button::Button() {
    setZValue(150);
}

int Button::GetButtonID() {
    return button_id;
}

void Button::Reset() {
    setPixmap(QPixmap(image_directory));
}

void Button::VirtualClick() {
    if(game_manager_proxy->GetClickedButton() != -1){
        all_buttons[game_manager_proxy->GetClickedButton()]->Reset();
    }
    game_manager_proxy->ButtonCommand(button_id);
    setPixmap(QPixmap(clicked_image_directory));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    VirtualClick();
}

///////////////////////////////////////////////////////////////////////////
/// \brief MoveButton::MoveButton
///
///
MoveButton::MoveButton() {
    all_buttons[MOVEBUTTON] = this;
    setPixmap(QPixmap(":/images/movebutton.png"));//
    button_id = MOVEBUTTON;
    image_directory = ":/images/movebutton.png";
    clicked_image_directory = ":/images/movebuttonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief RemoteAttackButton::RemoteAttackButton
///
///
RemoteAttackButton::RemoteAttackButton() {
    all_buttons[REMOTEATTACKBUTTON] = this;
    setPixmap(QPixmap(":/images/remoteattackbutton.png"));//
    button_id = REMOTEATTACKBUTTON;
    image_directory = ":/images/remoteattackbutton.png";
    clicked_image_directory = ":/images/remoteattackbuttonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief BomberButton::BomberButton
///
///
BomberButton::BomberButton() {
    all_buttons[BOMBERBUTTON] = this;
    setPixmap(QPixmap(":/images/bomberbutton.png"));//
    button_id = BOMBERBUTTON;
    image_directory = ":/images/bomberbutton.png";
    clicked_image_directory = ":/images/bomberbuttonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief ExtractionButton::ExtractionButton
///
///
ExtractionButton::ExtractionButton() {
    all_buttons[EXTRACTIONBUTTON] = this;
    setPixmap(QPixmap(":/images/extractionbutton.png"));//
    button_id = EXTRACTIONBUTTON;
    image_directory = ":/images/extractionbutton.png";
    clicked_image_directory = ":/images/extractionbuttonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateWorkerButton::CreateWorkerButton
///
///
CreateWorkerButton::CreateWorkerButton() {
    all_buttons[CREATEWORKERBUTTON] = this;
    setPixmap(QPixmap(":/images/createworkerbutton.png"));//
    button_id = CREATEWORKERBUTTON;
    image_directory = ":/images/createworkerbutton.png";
    clicked_image_directory = ":/images/createworkerbuttonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateSoldierButton::CreateSoldierButton
///
///
CreateSoldierButton::CreateSoldierButton() {
    all_buttons[CREATESOLDIERBUTTON] = this;
    setPixmap(QPixmap(":/images/soldiericon.png"));//
    button_id = CREATESOLDIERBUTTON;
    image_directory = ":/images/soldiericon.png";
    clicked_image_directory = ":/images/soldiericonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateDefenceTowerButton::CreateDefenceTowerButton
///
///
CreateDefenceTowerButton::CreateDefenceTowerButton() {
    all_buttons[CREATEDEFENCETOWERBUTTON] = this;
    setPixmap(QPixmap(":/images/defencetowericon.png"));//
    button_id = CREATEDEFENCETOWERBUTTON;
    image_directory = ":/images/defencetowericon.png";
    clicked_image_directory = ":/images/defencetowericonclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateCastleButton::CreateCastleButton
///
///
CreateCastleButton::CreateCastleButton() {
    all_buttons[CREATECASTLEBUTTON] = this;
    setPixmap(QPixmap(":/images/castleicon.png"));//
    button_id = CREATECASTLEBUTTON;
    image_directory = ":/images/castleicon.png";
    clicked_image_directory = ":/images/castleiconclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateHovelButton::CreateHovelButton
///
///
CreateHovelButton::CreateHovelButton() {
    all_buttons[CREATEHOVELBUTTON] = this;
    setPixmap(QPixmap(":/images/hovelicon.png"));//
    button_id = CREATEHOVELBUTTON;
    image_directory = ":/images/hovelicon.png";
    clicked_image_directory = ":/images/hoveliconclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateMilitaryHouseButton::CreateMilitaryHouseButton
///
///
CreateMilitaryHouseButton::CreateMilitaryHouseButton() {
    all_buttons[CREATEMILITARYHOUSEBUTTON] = this;
    setPixmap(QPixmap(":/images/militaryhouseicon.png"));//
    button_id = CREATEMILITARYHOUSEBUTTON;
    image_directory = ":/images/militaryhouseicon.png";
    clicked_image_directory = ":/images/militaryhouseiconclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateWoodButton::CreateWoodButton
///
///
CreateWoodButton::CreateWoodButton() {
    all_buttons[CREATEWOODBUTTON] = this;
    setPixmap(QPixmap(":/images/woodicon.png"));//
    button_id = CREATEWOODBUTTON;
    image_directory = ":/images/woodicon.png";
    clicked_image_directory = ":/images/woodiconclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CreateStoneButton::CreateStoneButton
///
///
CreateStoneButton::CreateStoneButton() {
    all_buttons[CREATESTONEBUTTON] = this;
    setPixmap(QPixmap(":/images/stoneicon.png"));//
    button_id = CREATESTONEBUTTON;
    image_directory = ":/images/stoneicon.png";
    clicked_image_directory = ":/images/stoneiconclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief CompleteBiuldinButton::CompleteBiuldinButton
///
///
CompleteBiuldinButton::CompleteBiuldinButton() {
    all_buttons[COMPLETEBIULDING] = this;
    setPixmap(QPixmap(":/images/completebiulding.png"));//
    button_id = COMPLETEBIULDING;
    image_directory = ":/images/completebiulding.png";
    clicked_image_directory = ":/images/completebiuldingclicked.png";
}
///////////////////////////////////////////////////////////////////////////
/// \brief SaveIcon::SaveIcon
///
///
SaveButton::SaveButton() {
     setPixmap(QPixmap(":/images/saveicon.png"));//
     button_id = SAVEBUTTON;
}
