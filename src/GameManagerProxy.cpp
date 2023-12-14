#include "GameManagerProxy.h"


GameManagerProxy::GameManagerProxy() {
    //external_button_id = -1;
    scene_rect_deviation = QPair<int, int>(0,0);
    Clear();
}

void GameManagerProxy::Report(QPair<int, int> _reporter_item) {
    reporter_item = _reporter_item;
}

void GameManagerProxy::ButtonCommand(int _button_id) {
    button_id = _button_id;
}

void GameManagerProxy::SetSceneRectDeviation(QPair<int, int> _scene_rect_deviation) {
    scene_rect_deviation = _scene_rect_deviation;
}
/*
void GameManagerProxy::ExternalButtonCommand(int _external_button_id) {
    external_button_id = _external_button_id;
}
*/
QPair<int, int> GameManagerProxy::GetClickedItem() {
    return reporter_item;
}

QPair<int, int> GameManagerProxy::GetSceneRectDeviation() {
    return scene_rect_deviation;
}

int GameManagerProxy::GetClickedButton() {
    return button_id;
}
/*
int GameManagerProxy::GetExternalClickedButton() {
    return external_button_id;
}
*/
void GameManagerProxy::Clear() {
    reporter_item = QPair<int, int> (-1, -1);
    button_id = -1;
}
