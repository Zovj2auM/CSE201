#include "listheaders.h"

Player::Player(QGraphicsItem* parent) :
    QObject (), QGraphicsPixmapItem (parent)
{
    create_animation();

    create_collision_range();

    this->setZValue(layer_player);

    for(int i = 0 ; i < 3 ; i ++)
    {
        colliding_items.push_back(QList<QGraphicsItem *>{});
        collision.push_back(true);
    }


    // Timer
    QTimer * timer = new QTimer();

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(30);
}

/**NOTE:
 *  FOR THE moment i made it so the player chooses the items he throws just for testing collisions
 * the designs i made are shit and i know it but again its just to test
 *
 * - adrien
 * **/

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
    {
        pressed_left = true;
        break;
    }
    case Qt::Key_Right:
    {
        pressed_right = true;
        break;
    }
    case Qt::Key_Up:
    {
        jump();
        break;
    }
    case Qt::Key_Space:
    {
        throw_projectile();
        break;
    }
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    {
        pressed_left = false;
        break;
    }
    case Qt::Key_Right:
    {
        pressed_right = false;
        break;
    }
    }
}
/**

bool Player::collision_right()
{
    if (speed.x > 0)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            for (int i = 0; i < size; i += 1)
            {
                if ((*iter)-> contains(QPointF(x() + (size) + (speed.x-1)  - (*iter)->x() , y() + i    -(*iter)->y() )))
                {
                    return true;
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
            for (int i = 0; i< size; i += 1)
            {
                if ((*iter)-> contains(QPointF(x() + (speed.x)  - (*iter)->x() , y() + i   -(*iter)->y() )))
                {
                    return true;
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
            for (int i = 0; i< size; i += 1)
            {
                if ((*iter)-> contains(QPointF(x() + i  - (*iter)->x() , y() + (speed.y)  -(*iter)->y() )))
                {
                    return true;
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
            for (int i = 0; i<size; i += 1)
            {
                if ((*iter)-> contains(QPointF(x() + i - (*iter)->x() , y() + (size) + (speed.y-1 )  - (*iter)->y() )))
                {
                    return true;
                }
            }
        }
    }
    return false;

}

bool Player::collision_b_l() //spots if the bottom left corner endures a collision both from the left and the bottom
{
    bool l = collision_left();
    bool b = collision_down();
    if(speed.y > 0 && speed.x < 0 && l == false && b == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(bottom left, (0,36)
            if ((*iter)-> contains(QPointF(x() + (speed.x)  - (*iter)->x() , y() + (size) + (speed.y - 1)   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}

bool Player::collision_b_r() // spots if the bottom right corner endures a collision both from the right and the bottom
{
    bool r = collision_right();
    bool b = collision_down();
    if(speed.y > 0 && speed.x > 0 && r == false && b == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(bottom right, (36,36)
            if ((*iter)-> contains(QPointF(x() + size + (speed.x - 1)  - (*iter)->x() , y() + (size) + (speed.y - 1)   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}

bool Player::collision_t_l()
{
    bool l = collision_left();
    bool t = collision_up();
    if(speed.y < 0 && speed.x < 0 && l == false && t == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(top left (0,0))
            if ((*iter)-> contains(QPointF(x() + speed.x - (*iter)->x() , y() + speed.y   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}

bool Player::collision_t_r()
{
    bool r = collision_right();
    bool t = collision_up();
    if(speed.y < 0 && speed.x > 0 && r == false && t == false)
    {
        QList<QGraphicsItem *> colliding_items = collision_range->collidingItems();
        for(auto iter = colliding_items.begin(); iter != colliding_items.end();iter++) //ITERATE OVER THE COLLIDING ITEMS
        {
            //(top right (36,0))
            if ((*iter)-> contains(QPointF(x() + size + speed.x-1 - (*iter)->x() , y() + speed.y   -(*iter)->y() )))
            {
                return true;
            }
        }
    }
    return false;
}
**/
void Player::move()
{
    //Accelerate
    speed.y += 1;

    if(count_super_fast > 0)
    {
        if(count_super_fast >= 10000)
        {
            count_super_fast = 0;
            max_speed = absolute_max_speed;
        }
        else
        {
            count_super_fast ++;
        }
    }

    if(count_super_throw > 0)
    {
        if(count_super_throw >= 10000)
        {
            count_super_throw = 0;
            current_projectile = 1;
        }
        else
        {
            count_super_throw ++;
        }
    }



    //Motion smooth
    if (pressed_left)
    {
        if (speed.x>-max_speed.x)
        {
            speed.x -= 1;
        }
    }
    else
    {
        if (speed.x<0)
        {
            speed.x = (speed.x < -1) ? speed.x/2 : 0;
        }
    }

    if (pressed_right)
    {
        if (speed.x<max_speed.x*((super_fast) ? 2 : 1))
        {
            speed.x += 1;
        }
    }
    else
    {
        if (speed.x>0)
        {
            speed.x = (speed.x > 1) ? speed.x/2 : 0;
        }
    }

    if (speed.y > max_speed.y)
    {
        speed.y = max_speed.y;
    }
    else if (speed.y < -max_speed.y)
    {
        speed.y = -max_speed.y;
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

    collision_ranges[0]->setRect(0,1,speed.x,size-1);
    collision_ranges[0]->setPos((speed.x > 0) ? size+1 : -1,0);

    collision_ranges[1]->setRect(1,0,size-1,speed.y);
    collision_ranges[1]->setPos(0,(speed.y > 0) ? size+1 : -1);

    collision_ranges[2]->setRect(0,0,speed.x,speed.y);
    collision_ranges[2]->setPos((speed.x > 0) ? size+1 : -1, (speed.y > 0) ? size+1 : -1);

    for(int i = 0; i < 3 ; i ++)
    {
        colliding_items[i] = collision_ranges[i]->collidingItems();
        collision[i] = false;
    }

    for(unsigned int i = 0; i < 3 ; i ++)
    {
        for(int j = 0; j < colliding_items[i].size(); j++)
        {
            if(typeid(*(colliding_items[i][j])) == typeid(Base_block))
            {
                collision[i] = true;

                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Small_collectable))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                coin_counter->add_coin();
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_1))
            {
                view->scene()->removeItem((colliding_items[i][j]));

                count_super_fast = 1;

                max_speed.x = absolute_max_speed.x*2;

                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_2))
            {
                view->scene()->removeItem((colliding_items[i][j]));

                current_projectile = 2;

                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_3))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_4))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_5))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_6))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_7))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Power_up_8))
            {
                view->scene()->removeItem((colliding_items[i][j]));
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(QGraphicsRectItem))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Collectable))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Enemy_projectile_1))
            {
                view->setScene(new QGraphicsScene());
                view->level_load->load_level(":/Images/Levels/test_world_enemies.png");
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Player_projectile_1))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Player_projectile_2))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Player_projectile_3))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Projectile))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Counter))
            {
                continue;
            }
            else if(typeid(*(colliding_items[i][j])) == typeid(Active_block))
            {

                view->scene()->addItem(new Activated_block(pair{(*(colliding_items[i][j])).x(),(*(colliding_items[i][j])).y()}));

                view->scene()->addItem(new Power_up_1(pair{(*(colliding_items[i][j])).x(),(*(colliding_items[i][j])).y()},block_size));

                view->scene()->removeItem(colliding_items[i][j]);
                continue;
            }
        }
    }

    // movements of the player:
    if (collision[0])
    {
        speed.x = 0;
    }
    if (collision[1])
    {
        speed.y = 0;
    }
    if (collision[2] && !collision[1] && !collision[0])
    {
        speed.y = 0;
    }

    //Jump reset
    if(collision[1] && speed.y >= 0)
    {
        times_jumped = 0;
    }


    //Direction of the player:
    if (speed.x>0)
    {
        facing = Right;
    }
    else if (speed.x<0)
    {
        facing = Left;
    }


    //superpowers timer
    if (super)
    {
        count_super += 1;
    }
    if (count_super > 50)
    {
        super = false;
    }

    if (super_fast)
    {
        count_super +=1;
    }
    if (count_super > 50)
    {
        super_fast = false;
    }

    if (super_throw)
    {
        count_super +=1;
    }
    if (count_super > 50)
    {
        super_fast = false;
    }

    //animation
    count += 0.4;

    set_animation_state();

    if (count >= maxFrame[state])
    {
        count = 0;
    }
    if (count < 0)
    {
        count = maxFrame[state]-0.00001;
    }

    setPixmap(animations[super][facing][state][int(count)]);

    setPos(x()+speed.x,y()+speed.y);

    view->centerOn(this->x(), 0);

    view->update_background();
}

void Player::create_collision_range()
{
    for(int i = 0; i < 3 ; i ++)
    {
        collision_ranges.push_back(new QGraphicsRectItem(this));
        collision_ranges[i]->setPen(QPen(Qt::NoPen));
    }
}

void Player::throw_projectile()
{

    // for the directino of the projectile: define a "last velocity speed"
    // then the direction is the direction of this last velocity
    pair position{x(),y()};

    switch (current_projectile)
    {
    case 1:
    {
        view->scene()->addItem(new Player_projectile_1(position, facing, size));
        break;
    }

    case 2:
    {
        view->scene()->addItem(new Player_projectile_2(position, facing, size));
        break;
    }

    case 3:
    {
        view->scene()->addItem(new Player_projectile_3(position, facing, size));
        break;
    }

    case 4:
    {
        view->scene()->addItem(new Enemy_projectile_1(position, facing, size));
        break;
    }
    }
}

void Player::superpower(Collectable collectable)
{
    if (collectable.type == star) //mario clignotte
    {
        count_super = 0;
        super = true;
    }

    if (collectable.type == mushroom) // mario goes two times faster
    {
        count_super_fast = 0;
        speed.x *= 2;
        super_fast = true;
    }

    if (collectable.type == eclair) //mario has a new projectile
    {
        count_super_throw = 0;
        view->scene()->addItem(new Player_projectile_3(pair{x(),y()}, facing, size));
        super_throw = true;
    }

    if (collectable.type == cheese) //Mario invicible ?
    {
        count_super = 0;

    }

    if (collectable.type == croissant) //mario slower
    {
        count_super_fast = 0;
        speed.x = speed.x/2;
        super_fast = true;
    }

    if (collectable.type == chocolatine) //mario grows two times bigger
    {
        count_super_big = 0;
        super_big = true;
    }

    if (collectable.type == mini_eiffel) //new projectile
    {
        count_super_throw = 0;
        view->scene()->addItem(new Player_projectile_3(pair{x(),y()}, facing, size));
        super_throw = true;
    }

    if (collectable.type == glass_wine) //mario grows two times bigger + clignotte
    {
        count_super_big = 0;
        size*=2;
        super_big = true;
        super = true;
    }

    if (collectable.type == coin) // no superpower, use for the coincounter to count the points
    {

    }
}

void Player::set_animation_state()
{
    switch(state)
    {
        case jumpH:
            if (count>=maxFrame[jumpH])
            {
                state = fallH;
            }
            break;

        case landH:
            if (count>=maxFrame[landH])
            {
                state = run;
            }
            break;

        case jumpV:
            if (count>=maxFrame[jumpV])
            {
                state = fallV;
            }
            break;

        case landV:
            if (count>=maxFrame[landV])
            {
                state = stand;
            }
            break;

        default:
            if (collision[1] && speed.y >= 0)
            {
                if (state==fallH)
                {
                    state = landH;
                }
                else if (state == fallV)
                {
                    state = landV;
                }
                else if (speed.x == 0.0)
                {
                    state = stand;
                }
                else
                {
                    state = run;
                }
            }
            else
            {
                if (speed.x == 0.0)
                {
                    state = fallV;
                }
                else
                {
                    state = fallH;
                }
            }
    }

    if (state != old_state)
    {
        old_state = state;
        count = 0;
    }
}

void Player::jump()
{
    if(times_jumped >= max_consecutive_jumps)
    {
        return;
    }
    times_jumped ++;
    speed.y -= max_speed.y;
    if (speed.x == 0.0)
    {
        state = jumpV;
    }
    else
    {
        state = jumpV;
    }
}

void Player::create_animation()
{
    QPixmap imgChar(gtexture->get_path_to(basic_player));

    for (int j = 0; j<number_of_character_states; j++)
    {
        for (int i = 0; i<maxFrame[j]; i++)
        {
            //generate images looking left
            animations[0][1][j][i] = imgChar.copy(i*size, j*size, size, size);

            //generate images looking right
            QImage img = imgChar.copy(i*size, j*size, size, size).toImage();
            img = img.mirrored(true, false);
            animations[0][0][j][i] = QPixmap::fromImage(img);


            //Generate super images looking left
            animations[1][1][j][i] = imgChar.copy(i*size, (number_of_character_states+j)*size, size, size);

            //Generate super images looking right
            QImage imgs = imgChar.copy(i*size, (number_of_character_states+j)*size, size, size).toImage();
            imgs = imgs.mirrored(true, false);
            animations[1][0][j][i] = QPixmap::fromImage(imgs);

        }
    }
}


