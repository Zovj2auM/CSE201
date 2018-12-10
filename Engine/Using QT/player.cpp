#include "player.h"
#include "view.h"
#include <QtDebug>
#include <QTimer>
#include <cmath>
#include "projectile.h"

Player::Player(QGraphicsItem* parent, int size ) : QObject (), QGraphicsPixmapItem (parent)
{

    create_animation();

    setPixmap(animations[0][0]);


    // Attributes
    count = 0;

    speed = pair{0,0};

    speedMax = pair{10,15};

    block_size = 18;

    direction = 1; //0 = left, 1 = right

    this->size = size;


    // Timer
    QTimer * timer = new QTimer();

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(20);

    // Create collision Range
    create_collision_range();
}

/**NOTE:
 *  FOR THE moment i made it so the player chooses the items he throws just for testing collisions
 * the designs i made are shit and i know it but again its just to test
 *
 * - adrien
 *
 *
 *
 *
 * **/

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        pressedL=true;
    }
    else if (event->key() == Qt::Key_Right)
    {
        pressedR=true;
    }
    else if (event->key() == Qt::Key_Up)
    {
        speed.y -= 10;
    }
    else if(event->key() == Qt::Key_1)
    {
        throwprojectile(1);
    }

    else if(event->key() == Qt::Key_2)
    {
        throwprojectile(2);
    }

    else if(event->key() == Qt::Key_3)
    {
        throwprojectile(3);
    }

}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        pressedL = false;
    }
    else if (event->key() == Qt::Key_Right)
    {
        pressedR = false;
    }
}


bool Player::collision_right()
{
    if (speed.x > 0)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            if (speed.y == 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + (size-1) + (speed.x)  - (*iter)->x() , y() + i    -(*iter)->y() )))
                    {
                        qDebug() << " speed.x > 0,speed.y == 0";

                        return true;
                    }
                }
            }

            else if (speed.y < 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + (size-1) + (speed.x)  - (*iter)->x() , y() + i + (speed.y + 1)   -(*iter)->y() )))
                    {
                        qDebug() << " speed.x > 0, speed.y < 0";
                        return true;
                    }
                }
            }

            else if (speed.y > 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + (size-1) + (speed.x)  - (*iter)->x() , y() + i + (speed.y-1)   -(*iter)->y() )))
                    {
                        qDebug() << "speed.x > 0 , speed.y > 0";

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Player::collision_left()
{
    if (speed.x < 0)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            if (speed.y == 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + (speed.x)  - (*iter)->x() , y() + i   -(*iter)->y() )))
                    {
                        qDebug() << "speed.x < 0 , speed.y == 0";

                        return true;
                    }
                }
            }

            else if (speed.y < 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + (speed.x)  - (*iter)->x() , y() + i + (speed.y + 1)  -(*iter)->y() )))
                    {
                        qDebug() << "speed.x < 0 , speed.y < 0";
                        return true;
                    }
                }
            }
            else if (speed.y > 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + (speed.x)  - (*iter)->x() , y() + i + (speed.y - 1)    -(*iter)->y() )))
                    {
                        qDebug() << "speed.x < 0 , speed.y > 0";
                        return true;
                    }
                }
            }

        }
    }
    return false;
}

bool Player::collision_up()
{
    if (speed.y < 0)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            if (speed.x == 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + i - (*iter)->x() , y() + (speed.y)  -(*iter)->y() )))
                    {
                        qDebug() << "speed.y < 0 , speed.x ==  0";

                        return true;
                    }
                }
            }

            else if (speed.x < 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + i + (speed.x+1)  - (*iter)->x() , y() + (speed.y)  -(*iter)->y() )))
                    {
                        qDebug() << "speed.y < 0 , speed.x <  0";

                        return true;
                    }
                }
            }


            else if (speed.x > 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + i + (speed.x-1)  - (*iter)->x() , y() + (speed.y)  -(*iter)->y() )))
                    {
                        qDebug() << "speed.y < 0 , speed.x >  0";

                        return true;
                    }
                }
            }

        }
    }
    return false;
}

bool Player::collision_down()
{
    if (speed.y > 0)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            if (speed.x == 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + i - (*iter)->x() , y() + (size-1) + (speed.y)  - (*iter)->y() )))
                    {
                        qDebug() << "speed.y > 0 , speed.x ==  0";

                        return true;
                    }
                }
            }

            else if (speed.x < 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + i + (speed.x+1)  - (*iter)->x() , y() + (size-1) + (speed.y)  -(*iter)->y() )))
                    {
                        qDebug() << "speed.y > 0 , speed.x <  0";
                        return true;
                    }
                }

            }


            else if (speed.x > 0)
            {
                for (int i = 0; i<size; i += 1)
                {
                    if ((*iter)-> contains(QPointF(x() + i + (speed.x-1) - (*iter)->x() , y() + (size-1) + (speed.y)  - (*iter)->y() )))
                    {
                        qDebug() << "speed.y > 0 , speed.x >  0";
                        return true;
                    }
                }
            }

        }
    }
    return false;

}


void Player::move()
{
    speed.y += 1;

    //Motion smooth
    if (pressedL){
        if (speed.x>-speedMax.x){speed.x -= 1;}
    }
    else{
        if (speed.x<-1){speed.x -= speed.x/2;}
        else if (speed.x<0){speed.x=0;}
    }
    if (pressedR){
        if (speed.x<speedMax.x){speed.x += 1;}
    }
    else{
        if (speed.x>1){speed.x -= speed.x/2;}
        else if (speed.x>0){speed.x=0;}
    }
    if (speed.y > speedMax.y)
    {
        speed.y = speedMax.y;
    }
    if (speed.y < -speedMax.y)
    {
        speed.y = -speedMax.y;
    }



    //in boundaries
    if(y() >= view->world_size.bottom)
    {
        speed.y = (0 > speed.y) ? speed.y : 0 ;
        setY(view->world_size.bottom);
    }
    else if(y() <= view->world_size.top)
    {
        speed.y = (0 < speed.y) ? speed.y : 0 ;
        setY(view->world_size.top);
    }

    if(x()<=view->world_size.left)
    {
        speed.x = (0 < speed.x) ? speed.x : 0 ;
        setX(view->world_size.left);
    }
    else if(x() >= view->world_size.right)
    {
        speed.x = (0 > speed.x) ? speed.x : 0 ;
        setX(view->world_size.right);
    }

    //animation
    if (speed.x<0){count -= 0.1;}
    else{count += 0.1;}

    if (count>=N){count = 0;}
    if (count< 0){count = N-0.00001;}

    if (speed.x<0){
        if (speed.y<0){
            setPixmap(animations[7][int(count)]);//flip
        }
        else{
            setPixmap(animations[8][int(count)]);//flip
        }
    }
    else if(speed.x>0){
        if (speed.y<0){
            setPixmap(animations[2][int(count)]);
        }
        else{
            setPixmap(animations[3][int(count)]);
        }
    }
    else{
        if (speed.y<0){
            setPixmap(animations[1][int(count)]);
        }
        else{
            setPixmap(animations[0][int(count)]);
        }
    }


    bool r = collision_right();
    bool l = collision_left();
    bool t = collision_up();
    bool b = collision_down();

    qDebug() << "==========";
    qDebug() << r;
    qDebug() << l;
    qDebug() << t;
    qDebug() << b;

    // movements of the player:


    if (r == true){speed.x = 0;}
    if (l == true){speed.x = 0;}
    if (t == true){speed.y = 0;}
    if (b == true){speed.y = 0;}


    //Direction of the player:
    if (pressedR){direction = 1;}
    if (pressedL){direction = 0;}

    setPos(x()+speed.x,y()+speed.y);

    view->centerOn(this);
}

void Player::throwprojectile(int i)
{

    // for the directino of the projectile: define a "last velocity speed"
    // then the direction is the direction of this last velocity
    if(i == 1)
    {
        if (direction == 1)
        {   // the player faces right, the projectile is thrown to the right
            Projectile* projectile = new Projectile(pair{int(x() + size ),int(y() +  size/4)}, direction, Projectile_type{baguette});
            view->scene->addItem(projectile);
        }
        else
        {   //the player faces left, the projectile is thrown to the left, and initial position just left of the player
            // -19... we would like -projectile.size.x - 1
            Projectile* projectile = new Projectile(pair{int(x() -19 ),int(y() +  size/4)}, direction, Projectile_type{baguette});
            view->scene->addItem(projectile);
        }
    }

    if(i == 2)
    {
        if (direction == 1)
        {   // the player faces right, the projectile is thrown to the right
            Projectile* projectile = new Projectile(pair{int(x() + size ),int(y() +  size/4)}, direction, Projectile_type{wine});
            view->scene->addItem(projectile);
        }
        else
        {   //the player faces left, the projectile is thrown to the left, and initial position just left of the player
            // -19... we would like -projectile.size.x - 1
            Projectile* projectile = new Projectile(pair{int(x() -19 ),int(y() +  size/4)}, direction, Projectile_type{wine});
            view->scene->addItem(projectile);
        }
    }

    if(i == 3)
    {
        if (direction == 1)
        {   // the player faces right, the projectile is thrown to the right
            Projectile* projectile = new Projectile(pair{int(x() + size ),int(y() +  size/4)}, direction, Projectile_type{smoke});
            view->scene->addItem(projectile);
        }
        else
        {   //the player faces left, the projectile is thrown to the left, and initial position just left of the player
            // -19... we would like -projectile.size.x - 1
            Projectile* projectile = new Projectile(pair{int(x() -19 ),int(y() +  size/4)}, direction, Projectile_type{smoke});
            view->scene->addItem(projectile);
        }
    }
}

void Player::create_animation()
{
    QPixmap imgChar(":/images/characterT.png");

    for (int j = 0; j<M-toMirror; j++)
    {
        for (int i = 0; i<N; i++)
        {
            animations[j][i] = imgChar.copy(i*size, j*size, size, size);
        }
    }

    QImage img = imgChar.toImage();
    QImage imgM = img.mirrored(true, false);
    QPixmap mirrored = QPixmap::fromImage(imgM);


    int lines[toMirror];

    lines[0] = 1; lines[1] = 2; lines[2] = 3; lines[3] = 5;

    for (int j = 0; j<toMirror; j++)
    {
        for (int i = 0; i<N; i++)
        {
            animations[j+(M-toMirror)][i] = mirrored.copy(i*size, lines[j]*size, size, size);
        }
    }
}

void Player::create_collision_range()
{
    collision_range = new QGraphicsRectItem(this);

    collision_range->setRect(0,0,size + size/2, size + size/2);

    collision_range->setPos(x() - size /4 ,y() - size / 4); //we readjust the position of the collision box so that is centers the player

    collision_range->setPen(QPen(Qt::NoPen));
}
