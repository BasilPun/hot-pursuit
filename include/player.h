#pragma once
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed.h>

class Player
{
public:
    bn::sprite_ptr sprite;
    bn::fixed speed;
    bn::size size;
    bn::rect bounding_box;

    Player(bn::fixed x_start, bn::fixed y_start);

    void update();
private:
    //
};