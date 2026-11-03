#include "player.h"
#include <bn_keypad.h>
#include <bn_display.h>
#include "bn_sprite_items_knight.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;
static constexpr bn::size PLAYER_SIZE = {8, 8};

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

Player::Player(bn::fixed x_start, bn::fixed y_start) : sprite(bn::sprite_items::knight.create_sprite(x_start, y_start)),
                                                         speed(1.5),
                                                         size(PLAYER_SIZE),
                                                         bounding_box(create_bounding_box(sprite, size))
{
}

void Player::update()
{
    if (bn::keypad::right_held())
    {
        sprite.set_x(sprite.x() + speed);
    }
    if (bn::keypad::left_held())
    {
        sprite.set_x(sprite.x() - speed);
    }
    // TODO: Add logic for up and down
    if (bn::keypad::up_held())
    {
        sprite.set_y(sprite.y() - speed);
    }
    if (bn::keypad::down_held())
    {
        sprite.set_y(sprite.y() + speed);
    }
    // Screen Wrapping
    if (sprite.x() >= MAX_X)
    {
        sprite.set_x(MAX_X - 1);
    }
    else if (sprite.x() <= MIN_X)
    {
        sprite.set_x(MIN_X + 1);
    }
    if (sprite.y() >= MAX_Y)
    {
        sprite.set_y(MAX_Y - 1);
    }
    else if (sprite.y() <= MIN_Y)
    {
        sprite.set_y(MIN_Y - 1);
    }

    bounding_box = create_bounding_box(sprite, size);
}