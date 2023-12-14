#ifndef GAMEMANAGERPROXY_H
#define GAMEMANAGERPROXY_H

#include <QPair>

class GameManagerProxy{
public:
    GameManagerProxy();

    void Report(QPair <int, int> _reporter_item);
    void ButtonCommand(int _button_id);
    void SetSceneRectDeviation(QPair <int, int> _scene_rect_deviation);

    QPair <int, int> GetClickedItem();
    int GetClickedButton();
    QPair <int, int> GetSceneRectDeviation();

    void Clear();

private:
    QPair <int, int> reporter_item;
    QPair <int, int> scene_rect_deviation;
    int button_id;
};

#endif // GAMEMANAGERPROXY_H
