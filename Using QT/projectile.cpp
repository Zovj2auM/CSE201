#include "projectile.h"
#include "player.h"
#include "view.h"
#include <QtDebug>
#include <QTimer>
#include <QTime>

Projectile::Projectile(pair position, bool direction, Projectile_type type, Projectile_state state, QGraphicsItem* parent) :
    QObject (), QGraphicsPixmapItem (parent)
{
    //Attributes
    this -> type = type;

    this -> state = state;

    setup_projectile(direction);

    setPos(position.x, position.y);

    create_collision_range();



    QTimer * timer = new QTimer();

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(20);
}

void Projectile::setup_projectile(bool direction)
{
    greal velocity = 5;

    const char* image;

    //initializing life and size of projectile depending on it's type
    if (type == baguette)
    {
        life = 1000;

        size = pair{18,5};

        if (direction == 1)
        {
            speed = pair{velocity, 0};
        }
        else
        {
            speed = pair{-velocity, 0};
        }

        image = "baguette.png";
    }
    else if (type == smoke)
    {
        life = 400;

        size = pair {18,18};

        if (direction == 1)
        {
            speed = pair{velocity, 0};
        }
        else
        {
            speed = pair{-velocity, 0};
        }

        image =  "smoke.png";
    }
    else if (type == wine)
    {
        life = 50000;

        size = pair{18,18};

        if (direction == 1)
        {
            speed = pair{velocity,velocity};
        }
        else
        {
            speed = pair{-velocity,velocity};
        }

        image = "wine.png";
    }
    else if (type == pot)
    {
        life = 200000;

        size = pair{18,18};

        if(direction == 1)
        {
            speed = pair{velocity, -velocity + 3};
        }
        else
        {
            speed = pair{-velocity, -velocity + 3};
        }

        image = "pot.png";
    }
    setPixmap(QPixmap(add_dir("baguette.png")));
}

void Projectile::create_collision_range()
{
    collision_range_proj = new QGraphicsRectItem(this);

    collision_range_proj->setRect(0,0,size.x + size.x /2, size.y + size.y/2);

    collision_range_proj->setOpacity(0);

    collision_range_proj->setPos(-size.x/4,-size.y/4);

    //we readjust the position of the collision
    //box so that is centers the projectile
}

bool Projectile::collision_right()
{
    // return if the right of the projectile suffers a collision
    QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
    for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
    {
        if (speed.x > 0) //projectile moves right
        {
            for (int i = 0; i<size.y; i++) //iterate over the whole height of the projectile
            {
                if ((*iter)-> contains(QPointF(x() +  (size.x)  + (speed.x-1) - (*iter)->x() , y() + i -(*iter)->y() )))
                {
                    return true;
                }
            }
        }

    }
    return false;
}

bool Projectile::collision_left()
{
    QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
    for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
    {
    if (speed.x < 0) //projectile goes backwards
    {
        for (int i =0; i< size.y; i++)
        { //collision of the left of the projectile
            if ((*iter)-> contains(QPointF(x()  + speed.x   - (*iter)->x() , y() + i  -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    }
    return false;

}

bool Projectile::collision_up()
{
    QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
    for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
    {
        if (speed.y < 0)
        {
            for (int i =0; i< size.x; i++)
            { //collision of the top of the projectile
                if ((*iter)-> contains(QPointF(x()  + i  - (*iter)->x() , y() +speed.y -(*iter)->y() )))
                {
                    return true;
                }
            }
        }
    }
    return false;


}

bool Projectile::collision_down()
{
    QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
    for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
    {
        if(speed.y > 0)
        {
            for (int i =0; i< size.x; i++)
            { //collision of the bottom of the projectile
                if ((*iter)-> contains(QPointF(x()  + i  - (*iter)->x() , y() + (size.y-1) + (speed.y) -(*iter)->y() )))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Projectile::collision_b_l() //spots if the bottom left corner endures a collision both from the left and the bottom
{
    bool l = collision_left();
    bool b = collision_down();
    if(speed.y > 0 && speed.x < 0 && l == false && b == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(bottom left)
            if ((*iter)-> contains(QPointF(x() + (speed.x)  - (*iter)->x() , y() + (size.y) + (speed.y - 1)   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}

bool Projectile::collision_b_r() // spots if the bottom right corner endures a collision both from the right and the bottom
{
    bool r = collision_right();
    bool b = collision_down();
    if(speed.y > 0 && speed.x > 0 && r == false && b == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(bottom right)
            if ((*iter)-> contains(QPointF(x() + size.x + (speed.x - 1)  - (*iter)->x() , y() + (size.y) + (speed.y - 1)   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}

bool Projectile::collision_t_l()
{
    bool l = collision_left();
    bool t = collision_up();
    if(speed.y < 0 && speed.x < 0 && l == false && t == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(top left (0,0))
            if ((*iter)-> contains(QPointF(x() + speed.x  - (*iter)->x() , y() + speed.y   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}

bool Projectile::collision_t_r()
{
    bool r = collision_right();
    bool t = collision_up();
    if(speed.y < 0 && speed.x > 0 && r == false && t == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range_proj->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(top right (36,0))
            if ((*iter)-> contains(QPointF(x() + size.x + speed.x-1 - (*iter)->x() , y() + speed.y   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}


void delay(int i) //milliseconds
{
    QTime dieTime= QTime::currentTime().addMSecs(i);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Projectile::move()
{
    if (state == vanish){setPixmap(QPixmap(":/images/explosion.png")); state = dead ; delay(200); QObject::deleteLater();}

    life -= 10;
    if(life == 0)
    {
        speed.y = 5;
        setPos(x()+speed.x, y()+speed.y);
        return;
    }
    if(life == -10){delay(100); QObject::deleteLater();}

    int ac_vel_x = 2; //after collision velocity (when the projectile bounces)
    int ac_vel_y = 5;

    bool r = collision_right();
    bool l = collision_left();
    bool t = collision_up();
    bool b = collision_down();
    bool bl = collision_b_l();
    bool br = collision_b_r();
    bool tl = collision_t_l();
    bool tr = collision_t_r();

    if (r == true){speed.x = -ac_vel_x; speed.y = ac_vel_y;}
    if (l == true){speed.x = ac_vel_x; speed.y = ac_vel_y;}
    if (b == true){speed.y = 0; life = 10;}
    if (t == true){speed.y = ac_vel_y;}
    if (bl == true || br == true){speed.y = 0; speed.x = speed.x; life = 10;} //if the bottom corners collide, we maintain the velocity on x,
                                                                              //but not on y but we make the projectile almost dead
    if (tl == true || tr == true){speed.y = 0; speed.x = speed.x; life = 10;} //if the top corners collide, we maintain the velocity on x,
                                                                              //but not on y but we make the projectile almost dead


    setPos(x() + speed.x, y() + speed.y);
}
