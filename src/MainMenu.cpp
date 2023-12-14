#include "MainMenu.h"

MainMenu::MainMenu(){
    setPixmap(QPixmap(":/images/Back.png"));
    setPos(0, 0);

    SinglePlayerIcon * single_player_icon = new SinglePlayerIcon();
    single_player_icon->setPos(0, 0);

    MultiPlayIcon * multi_play_icon = new MultiPlayIcon();
    multi_play_icon->setPos(0, 0);

    MapEditorIcon * map_editor_icon = new MapEditorIcon();
    map_editor_icon->setPos(0, 0);

    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screen_width, screen_height);
    scene->addItem(this);
    scene->addItem(single_player_icon);
    scene->addItem(multi_play_icon);
    scene->addItem(map_editor_icon);

    QGraphicsView * view = new QGraphicsView(scene);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(screen_width, screen_height);
    view->showFullScreen();
}
