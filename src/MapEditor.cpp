#include "MapEditor.h"
#include <QDebug>
MapEditor::MapEditor() {
    map = new Map(30,32);//for example...
    //or:
    //file_manager = new FileManager();
    //map = file_manager->LoadData(":/images/map.map");
    //

    id=0;

    QVector<int> map_editor_button;

    map_editor_button.push_back(CREATEWORKERBUTTON);
    map_editor_button.push_back(CREATESOLDIERBUTTON);
    map_editor_button.push_back(CREATEDEFENCETOWERBUTTON);
    map_editor_button.push_back(CREATECASTLEBUTTON);
    map_editor_button.push_back(CREATEHOVELBUTTON);
    map_editor_button.push_back(CREATEMILITARYHOUSEBUTTON);
    map_editor_button.push_back(CREATEWOODBUTTON);
    map_editor_button.push_back(CREATESTONEBUTTON);

    game_manager_proxy = new GameManagerProxy();

    //check proxy.
    QTimer *check_proxy_timer = new QTimer();
    connect(check_proxy_timer,SIGNAL(timeout()),this,SLOT(CheckProxy()));
    check_proxy_timer->start(10);

    //scroll.
    QTimer *scroll_timer = new QTimer();
    connect(scroll_timer,SIGNAL(timeout()),this,SLOT(ScrollContent()));
    scroll_timer->start(10);

    //create buttons.
    new CreateWorkerButton();
    new CreateSoldierButton();
    new CreateDefenceTowerButton();
    new CreateCastleButton();
    new CreateHovelButton();
    new CreateMilitaryHouseButton();
    new CreateWoodButton();
    new CreateStoneButton();

    SaveButton * save_button = new SaveButton();
    save_button->setPos(10, 10);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screen_width, screen_height);

    map->Draw(scene);

    //set position.//add buttons to scene.
    for(int i = 0; i < map_editor_button.size(); i++){
        all_buttons[map_editor_button[i]]->setPos(10, 50 + 64 * i);
        scene->addItem(all_buttons[map_editor_button[i]]);
    }


    scene->addItem(save_button);

    view = new QGraphicsView(scene);
    view->setScene(scene);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(screen_width, screen_height);
    view->showFullScreen();

    all_buttons[CREATEWORKERBUTTON]->VirtualClick();
}

void MapEditor::CheckProxy() {
    int button = game_manager_proxy->GetClickedButton();
    QPair<int, int> location = game_manager_proxy->GetClickedItem();

    if(button == SAVEBUTTON){
        file_manager = new FileManager();
        file_manager->WriteData(map,"/home/saman/Desktop/map.map");
        qDebug()<<"map saved!";
        exit(0);
    }

    if(button != -1 && location != QPair<int, int>(-1, -1)){
        game_manager_proxy->Report(QPair<int, int>(-1, -1));//reset.
        switch (button) {
        case CREATEWORKERBUTTON:
            game_object = new Worker();
            break;
        case CREATESOLDIERBUTTON:
            game_object = new Soldier();
            break;
        case CREATEDEFENCETOWERBUTTON:
            game_object = new DefenseTower();
            break;
        case CREATECASTLEBUTTON:
            game_object = new Castle();
            break;
        case CREATEHOVELBUTTON:
            game_object = new Hovel();
            break;
        case CREATEMILITARYHOUSEBUTTON:
            game_object = new MilitaryHome();
            break;
        case CREATEWOODBUTTON:
            game_object = new Wood();
            break;
        case CREATESTONEBUTTON:
            game_object = new Stone();
            break;
        }
        game_object->SetID(id);
        game_object->SetLocation(location);
        map->Get(location)->Insert(game_object);
        map->DrawOneItem(location, scene);
        map->InsertObjectsAround(game_object, game_object->GetLocation(), 1, game_object->GetRadiousOnMap());
    }
}

void MapEditor::ScrollContent() {
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


MapEditorIcon::MapEditorIcon() {
    setPixmap(QPixmap(":/images/Map.png"));
}

void MapEditorIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    new MapEditor();
}
