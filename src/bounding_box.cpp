#include "bounding_box.h"

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(const bn::sprite_ptr &sprite, bn::size box_size)
{
    return bn::rect(
        sprite.x().round_integer(),
        sprite.y().round_integer(),
        box_size.width(),
        box_size.height());
}