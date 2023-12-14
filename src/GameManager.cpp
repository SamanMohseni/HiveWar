#include "GameManager.h"
#include <QDebug>

GameManager::GameManager(Map * _map, int _timeout){
    suspended_item = NULL;
    reporter_item = QPair<int, int>(-1, -1);
    in_task_mode = false;
    map = _map;
    timeout = _timeout;

    Vertical_scroll_id = Horizontal_scroll_id = 0;

    game_manager_proxy = new GameManagerProxy();

    //check proxy.
    QTimer *check_proxy_timer = new QTimer();
    connect(check_proxy_timer,SIGNAL(timeout()),this,SLOT(CheckProxy()));
    check_proxy_timer->start(10);

    //scroll.
    QTimer *scroll_timer = new QTimer();
    connect(scroll_timer,SIGNAL(timeout()),this,SLOT(ScrollContent()));
    scroll_timer->start(10);


    //task buttons:
    new MoveButton();
    new RemoteAttackButton();
    new BomberButton();
    new ExtractionButton();
    new CreateWorkerButton();
    new CreateSoldierButton();
    new CreateCastleButton();
    new CreateDefenceTowerButton();
    new CreateHovelButton();
    new CreateMilitaryHouseButton();
    new CompleteBiuldinButton();
    //

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screen_width, screen_height);

    map->Draw(scene);

    game_window = new GameWindow();
    game_window->Draw(scene);

    view = new QGraphicsView(scene);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(screen_width, screen_height);
    view->setBackgroundBrush(QColor(77,86,18));
    view->showFullScreen();
}

void GameManager::Refresh() {//if there is any lag after each turn the problem might be here.
    TaskClear();
    for(int i=0; i < highlighted_hexagons.size(); i++){
        highlighted_hexagons[i]->EraseHighlight();
    }
    for(int i = 0; i < on_screen_lines.size(); i++){
        delete on_screen_lines[i];
    }
    on_screen_lines.clear();
    map->Draw(scene);
    //game_window->Draw(scene);
}

void GameManager::ClearScreen() {
    map->Clear(scene);
}

void GameManager::Suspend(GameObject * _suspended_item){
    qDebug()<<"item suspended!";
    for (int i = 0; i < on_screen.size(); i++){
        scene->removeItem(on_screen[i]);
    }
    on_screen.clear();

    suspended_item = _suspended_item;
    suspended_item->ShowMenu(scene);//button menu.

    /*if(suspended_item->IsTasked()) {
        CancelTask();
        qDebug()<<"task canceled!";
    }*/
    game_window->ShowInfo(suspended_item);

}

void GameManager::Report(QPair<int, int> _reporter_item) {
    for(int i = MOVEBUTTON; i <= COMPLETEBIULDING; i++){
        all_buttons[i]->Reset();
    }
    if(suspended_item != NULL && map->Get(_reporter_item)->IsHighlighted()){
        for(int i=0; i < highlighted_hexagons.size(); i++){
            highlighted_hexagons[i]->EraseHighlight();
        }
        qDebug()<<"report";
        reporter_item = _reporter_item;      
        UpdateSuspendAndReporterItem();//if the move is legal.
    }
    else if(suspended_item == map->Get(_reporter_item)->ObjectInside()){
        for(int i=0; i < highlighted_hexagons.size(); i++){
            highlighted_hexagons[i]->EraseHighlight();
        }
        TaskClear();
    }
}

void GameManager::ButtonCommand(int _button_id){
    QVector<QPair<int, int> > *neighbours;
    Hexagon * tmp;

    if(button_id != _button_id){
        for(int i=0; i < highlighted_hexagons.size(); i++){
            highlighted_hexagons[i]->EraseHighlight();
        }

        button_id = _button_id;
        neighbours = map->GetHexagonsAround(suspended_item->GetLocation(), suspended_item->GetAttackStartPoint(), suspended_item->GetAttackRadius());

        switch (button_id) {
        case MOVEBUTTON:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    if(!tmp->IsComming() && (tmp->ObjectInside() == NULL || tmp->ItemHasLeft())){
                        tmp->Highlight();
                        highlighted_hexagons.push_back(tmp);
                    }
                }
            }
            break;
        case REMOTEATTACKBUTTON:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    tmp->Highlight();
                    highlighted_hexagons.push_back(tmp);
                }
            }
            break;
        case BOMBERBUTTON:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    tmp->Highlight();
                    highlighted_hexagons.push_back(tmp);
                }
            }
            break;
        case EXTRACTIONBUTTON:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    if(tmp->ObjectInside() != NULL){
                        if(tmp->ObjectInside()->GetObjectType() == type_stone || tmp->ObjectInside()->GetObjectType() == type_wood){
                            tmp->Highlight();
                            highlighted_hexagons.push_back(tmp);
                        }
                    }
                }
            }
            break;
        case CREATEWORKERBUTTON:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    if(!tmp->IsComming() && (tmp->ObjectInside() == NULL || tmp->ItemHasLeft())){
                        tmp->Highlight();
                        highlighted_hexagons.push_back(tmp);
                    }
                }
            }
            break;
        case CREATESOLDIERBUTTON:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    if(!tmp->IsComming() && (tmp->ObjectInside() == NULL || tmp->ItemHasLeft())){
                        tmp->Highlight();
                        highlighted_hexagons.push_back(tmp);
                    }
                }
            }
            break;
        case COMPLETEBIULDING:
            for(int i=0; i < neighbours->size(); i++){
                if((*neighbours)[i].first >= 0 && (*neighbours)[i].first < map->Width() && (*neighbours)[i].second >= 0 && (*neighbours)[i].second < map->Height()){
                    tmp = map->Get((*neighbours)[i]);
                    if(tmp->ObjectInside() != NULL){
                        if(tmp->ObjectInside()->GetObjectType() == type_castle_halfbiuld || tmp->ObjectInside()->GetObjectType() == type_defencetower_halfbiuld ||
                                tmp->ObjectInside()->GetObjectType() == type_hovel_halfbiuld || tmp->ObjectInside()->GetObjectType() == type_military_home_halfbiuld){
                            map->Get(tmp->ObjectInside()->GetLocation())->Highlight();
                            highlighted_hexagons.push_back(map->Get(tmp->ObjectInside()->GetLocation()));
                        }
                    }
                }
            }
            break;
        //////////////////////////////////////////////////////////
        case CREATECASTLEBUTTON:
            HighLightForWorker(suspended_item->GetLocation(),castle_radious);
            break;
        case CREATEDEFENCETOWERBUTTON:
            HighLightForWorker(suspended_item->GetLocation(),defense_tower_radious);
            break;
        case CREATEHOVELBUTTON:
            HighLightForWorker(suspended_item->GetLocation(),hovel_radious);
            break;
        case CREATEMILITARYHOUSEBUTTON:
            HighLightForWorker(suspended_item->GetLocation(),militaryhome_radious);
            break;
        }
        //////////////////////////////////////////////////////////
    }
}

void GameManager::HighLightForWorker(QPair<int, int> _center, int _biulding_radious) {
    Hexagon * tmp;
    bool IsOK;
    QVector<QPair<int, int> > *possible_refrence;
    possible_refrence = map->GetHexagonsAround(_center, _biulding_radious + 1, _biulding_radious + 2);

    QVector<QPair<int, int> > possible;
    for(int i = 0; i < possible_refrence->size(); i++){
        possible.push_back((*possible_refrence)[i]);
    }

    QVector<QPair<int, int> > *neighbours;
    for(int i = 0; i < possible.size(); i++){
        IsOK = true;
        if(possible[i].first >= 0 && possible[i].first < map->Width() && possible[i].second >= 0 && possible[i].second < map->Height()){
            tmp = map->Get(possible[i]);
            if(!tmp->IsComming() && (tmp->ObjectInside() == NULL || tmp->ItemHasLeft())){
                neighbours = map->GetHexagonsAround(possible[i], 1, _biulding_radious);
                for(int j = 0; j < neighbours->size(); j++){
                    if((*neighbours)[j].first >= 0 && (*neighbours)[j].first < map->Width() && (*neighbours)[j].second >= 0 && (*neighbours)[j].second < map->Height()){
                        tmp = map->Get((*neighbours)[j]);
                        if(tmp->IsComming() || (tmp->ObjectInside() != NULL && !tmp->ItemHasLeft())){
                            IsOK = false;
                        }
                    }
                    else{
                        IsOK = false;
                    }
                }
            }
            else{
                IsOK = false;
            }
        }
        else{
            IsOK = false;
        }
        if(IsOK){
            tmp = map->Get(possible[i]);
            tmp->Highlight();
            highlighted_hexagons.push_back(tmp);
        }
    }
}

void GameManager::DrawLine(QPair<int, int> _first_location, QPair<int, int> _next_location, int _color = 0) {
    float x1 = map->Get(_first_location)->x() + hexagon_width/2;
    float y1 = map->Get(_first_location)->y() + hexagon_height/2;
    float x2 = map->Get(_next_location)->x() + hexagon_width/2;
    float y2 = map->Get(_next_location)->y() + hexagon_height/2;
    float line_thickness = 1;
    float dx = pow((line_thickness*line_thickness)/(1+pow(((x2-x1+0.01)/(y1-y2+0.01)),2)),0.5);
    float dy = dx*((x2-x1+0.01)/(y1-y2+0.01));
    QVector<QPointF> points;
    points.push_back(QPointF(x1+dx*2,y1+dy*2));
    points.push_back(QPointF(x1-dx*2,y1-dy*2));
    points.push_back(QPointF(x2-dx/2,y2-dy/2));
    points.push_back(QPointF(x2+dx/2,y2+dy/2));
    QPolygonF polygon(points);
    QGraphicsPolygonItem * line = new QGraphicsPolygonItem(polygon);
    line->setBrush(QBrush(Qt::SolidPattern));
    switch (_color) {
    case 0:
        line->setBrush(QBrush(Qt::blue));
        break;
    case 1:
        line->setBrush(QBrush(Qt::red));
        break;
    case 2:
        line->setBrush(QBrush(Qt::green));
        break;
    case 3:
        line->setBrush(QBrush(Qt::yellow));
        break;
    }
    line->setZValue(102);
    scene->addItem(line);
    on_screen_lines.push_back(line);
}

void GameManager::UpdateSuspendAndReporterItem() {
    GameObject * tmp;
    QPair<int, int> location;
    switch (button_id) {
    case MOVEBUTTON:
        suspended_item->Move(reporter_item);
        map->Get(suspended_item->GetLocation())->ItemIsLeaving();
        map->Get(reporter_item)->Reserve(suspended_item);
        DrawLine(suspended_item->GetLocation(), reporter_item);
        break;
    case REMOTEATTACKBUTTON:
        suspended_item->RemoteAttack(reporter_item);
        DrawLine(suspended_item->GetLocation(), reporter_item, 1);
        break;
    case BOMBERBUTTON:
        suspended_item->Shoot(reporter_item);
        DrawLine(suspended_item->GetLocation(), reporter_item, 1);
        break;
    case EXTRACTIONBUTTON:
        suspended_item->RemoteAttack(reporter_item);
        suspended_item->SetBiuldingType(type_none);
        DrawLine(suspended_item->GetLocation(), reporter_item, 2);
        break;
    case CREATEWORKERBUTTON:
        suspended_item->Shoot(reporter_item);//shoot people to position.
        map->Get(reporter_item)->Reserve(suspended_item);
        break;
    case CREATESOLDIERBUTTON:
        suspended_item->Shoot(reporter_item);//shoot soldier to position.
        map->Get(reporter_item)->Reserve(suspended_item);
        break;
    case COMPLETEBIULDING:
        suspended_item->RemoteAttack(reporter_item);
        suspended_item->SetBiuldingType(type_biulding);
        DrawLine(suspended_item->GetLocation(), reporter_item, 3);
        break;
    //////////////////////////////////////////////////////////
    default:
        suspended_item->RemoteAttack(reporter_item);
        map->Get(reporter_item)->Reserve(suspended_item);
        location = reporter_item;
        switch (button_id) {
        case CREATECASTLEBUTTON:
            suspended_item->SetBiuldingType(type_castle);
            tmp = new CastleHalfBiuld();
            break;
        case CREATEDEFENCETOWERBUTTON:
            suspended_item->SetBiuldingType(type_defencetower);
            tmp = new DefenseTowerHalfBiuld();
            break;
        case CREATEHOVELBUTTON:
            suspended_item->SetBiuldingType(type_hovel);
            tmp = new HovelHalfBiuld();
            break;
        case CREATEMILITARYHOUSEBUTTON:
            suspended_item->SetBiuldingType(type_military_home);
            tmp = new MilitaryHomeHalfBiuld();
            break;
        }
        tmp->SetID(0);
        tmp->SetLocation(location);
        map->Get(location)->Insert(tmp);
        map->InsertObjectsAround(tmp, location, 1, tmp->GetRadiousOnMap());
        map->DrawOneItem(location, scene);
    }
    //////////////////////////////////////////////////////////
    suspended_item->SetTask();
    TaskClear();
}

/*void GameManager::CancelTask() {
}*/

void GameManager::TaskClear() {
    for (int i = 0; i < on_screen.size(); i++){
        scene->removeItem(on_screen[i]);
    }
    on_screen.clear();
    suspended_item = NULL;
    button_id = -1;
    reporter_item = QPair<int, int>(-1, -1);
    in_task_mode = false;
    game_manager_proxy->Clear();
}

void GameManager::CheckProxy() {
    int button = game_manager_proxy->GetClickedButton();
    QPair<int, int> location = game_manager_proxy->GetClickedItem();

    if(button != -1){
        in_task_mode = true;
        ButtonCommand(button);
    }

    if(in_task_mode){
        if(location != QPair<int, int>(-1, -1)){
            Report(location);
            game_manager_proxy->Clear();
        }
    }
    else if(location != QPair<int, int>(-1, -1)){
        if(map->Get(location)->ObjectInside() != NULL){
            if(map->Get(location)->ObjectInside()->IsTaskable() && map->Get(location)->ObjectInside()->GetID() == 0){
                Suspend(map->Get(location)->ObjectInside());
                game_manager_proxy->Report(QPair<int, int>(-1, -1));
            }
        }
    }
    //game_manager_proxy->Clear();
}

void GameManager::ScrollContent() {
    if(QCursor::pos().y() < 5){
        Vertical_scroll_id = 1;
    }
    else if(QCursor::pos().y() > screen_height - 5){
        Vertical_scroll_id = -1;
    }
    else{
        Vertical_scroll_id = 0;
    }
    if(QCursor::pos().x() < 5){
        Horizontal_scroll_id = 1;
    }
    else if(QCursor::pos().x() > screen_width - 5){
        Horizontal_scroll_id = -1;
    }
    else{
        Horizontal_scroll_id = 0;
    }

    int speed = 5;
    //scroll.
    if(Vertical_scroll_id != 0 || Horizontal_scroll_id != 0){
        scene->setSceneRect(scene->sceneRect().x()-speed*Horizontal_scroll_id,scene->sceneRect().y()-speed*Vertical_scroll_id,screen_width,screen_height);

        game_manager_proxy->SetSceneRectDeviation(QPair<int, int>(scene->sceneRect().x(),scene->sceneRect().y()));
    }
}

