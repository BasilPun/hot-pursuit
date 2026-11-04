#pragma once

#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_vector.h>
#include <bn_string.h>
#include "common_fixed_8x16_font.h"

static constexpr int MAX_SCORE_CHARS = 22;

class ScoreDisplay
{
public:
    int score = 0;
    int high_score = 0;
    int lives = 3;
    ScoreDisplay();

    /**
- Increases score by 1 and updates high score if needed. Displays score and high score.
     */
    void update();
    
    /**
- Sets score back to 0. Does NOT reset high score.
     */
    void resetScore();
private:
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> high_sprites;
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> lives_sprites;
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
    bn::sprite_text_generator text_generator;                  // Text generator for scores
};