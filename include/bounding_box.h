#pragma once

#include "bn_rect.h"
#include "bn_sprite_ptr.h"
#include "bn_size.h"

bn::rect create_bounding_box(const bn::sprite_ptr &sprite, bn::size box_size);
