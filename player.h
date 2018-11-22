#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Character.h"
using namespace std;

class Player: public Character
{
public:
    void goforward();
    void goback();
    void jump();//these moving parts should have a default speed so we dont put parametres
    void growbigger();
    void shrink();
    void stop();
};

#endif // PLAYER_H
