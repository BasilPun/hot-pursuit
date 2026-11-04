#include "scoredisplay.h"

static constexpr int HIGH_SCORE_X = -110;
static constexpr int HIGH_SCORE_Y = -72;
static constexpr int LIVES_X = -20;
static constexpr int LIVES_Y = -72;
static constexpr int SCORE_X = 50;
static constexpr int SCORE_Y = -72;

ScoreDisplay::ScoreDisplay() : score(0),                                                                 // Start score at 0
                                high_score(0),
                                lives(3),
                                high_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()),
                                lives_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()),                                                              // Start high score at 0
                                score_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()),             // Start with empty vector for score sprites
                                text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)) // Use a new text generator
{
}

void ScoreDisplay::update()
{
    // increase score and update high score if this is the new highest
    score++;
    if (score > high_score)
    {
        high_score = score;
    }

    // Stop displaying previous scores
    high_sprites.clear();
    score_sprites.clear();
    lives_sprites.clear();
    

    //DISPLAY HIGH SCORE
    bn::string<MAX_SCORE_CHARS> high_str = "High:";
    high_str.append(bn::to_string<16>(high_score));
    text_generator.generate(HIGH_SCORE_X,HIGH_SCORE_Y, high_str, score_sprites);

    //DISPLAY LIVES
    bn::string<MAX_SCORE_CHARS> lives_str = "Lives:";
    lives_str.append(bn::to_string<16>(lives));
    text_generator.generate(LIVES_X,LIVES_Y, lives_str, score_sprites);

    //DISPLAY SCORE
    bn::string<MAX_SCORE_CHARS> score_str = "Score:";
    score_str.append(bn::to_string<16>(score));
    text_generator.generate(SCORE_X,SCORE_Y, score_str, score_sprites);

}

void ScoreDisplay::resetScore()
{
    score = 0;
    lives = 3;
}