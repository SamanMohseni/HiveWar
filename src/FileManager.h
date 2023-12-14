#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDataStream>
#include <QByteArray>
#include <QString>
#include <QPair>
#include <QFile>

#include "AllGameObjects.h"
#include "Map.h"

class FileManager {
public:
    FileManager();
    Map * LoadData(QString _location);
    //reads map size and creates an empty map.//map automaticaly createds default hexagons.
    //loads data and reads and creates all GameObjects. using GameObjects filles hexagons.
    void WriteData(Map * _map, QString _location);//just saves map size and GameObjects.
private:
    void CreateRawData(Map * map);
private:
    QByteArray raw_data;
    Map * map;
};

#endif // FILEMANAGER_H
