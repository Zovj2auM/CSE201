#include "listheaders.h"

Game_over::Game_over(QGraphicsItem* parent):
    QObject(), QGraphicsPixmapItem (parent)
{
    view->player->setX(0);
    view->player->playing = false;
    setPos(0,-view->screen_size.y+18);
    QPixmap img(":/Images/Backgrounds/Main_background/game_over.png");
    img = img.scaled(view->screen_size.x, view->screen_size.y);
    setPixmap(img);
    QString score="Final Score:";
    QPainter painter(&img) ;
    painter.drawText(QPoint(5,25),score);
    view->music->stop();
}
