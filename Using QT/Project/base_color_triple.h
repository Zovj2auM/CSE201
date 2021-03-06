#ifndef BASE_COLOR_TRIPLE_H
#define BASE_COLOR_TRIPLE_H
#include "global.h"


class Base_color_triple
{
public:

    static constexpr int diff = 45;

    int r,g,b;

    View* view;

    virtual ~Base_color_triple(){}

    virtual void test(int R, int G, int B, pair& position, QGraphicsScene*scene){}
};

#endif // BASE_COLOR_TRIPLE_H
