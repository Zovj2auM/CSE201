#ifndef COLLECTABLE_H
#define COLLECTABLE_H 

#include <QGraphicsPixmapItem>
#include <QObject>
#include "tools.h"
#include "types_states_textures.h"

class Collectable : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:

    Collectable_type type;             // shows the kind of collectable the player meets

    Collectable_state state;           // shows if the collectable is used or unused

    Collectable_texture texture;       // the player meets the same or different collectable

    Collectable(pair position, int creator_object_size_y, pair size, QGraphicsItem* parent = 0 );

    // Attributes
    pair size, position, speed;
    int life; //some collectables have life even though they are not eaten (ex mushroom)

    QGraphicsRectItem* collision_range_collec;

    // Methods
    void collision_range();

    bool collision_left(), collision_down(), collision_up(), collision_right();

public slots:

    void move(); //next position of the collectable depending on their way of moving

};

#endif // COLLECTABLE_H