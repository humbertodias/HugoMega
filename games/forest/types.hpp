#ifndef FOREST_TYPES_HPP
#define FOREST_TYPES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "config.hpp"

class cgfFile;
class tilFile;
class oosFile;

typedef struct {
  Mix_Chunk *chunk;
  int loop_channel;
} ForestSound;

typedef struct {
  int is_til;
  tilFile *til;
  cgfFile *cgf;
  int start;
  int end;
  oosFile *sync;
} ForestAnim;

typedef struct {
  cgfFile *hugo_side;
  cgfFile *hugo_jump;
  cgfFile *hugo_crawl;
  ForestAnim hugo_telllives;
  cgfFile *hugo_hand1;
  cgfFile *hugo_hand2;

  cgfFile *catapult;
  cgfFile *trap;
  cgfFile *rock;
  cgfFile *tree;
  cgfFile *sack;
  cgfFile *lone_tree;

  cgfFile *bg_hillsday;
  cgfFile *bg_trees;
  cgfFile *bg_ground;
  cgfFile *grass;
  cgfFile *leaves1;
  cgfFile *leaves2;
  cgfFile *end_mountain;
  SDL_Surface *bg_gradient;
  SDL_Surface *scoreboard;

  cgfFile *score_numbers;
  cgfFile *hugo_lives;
  cgfFile *arrows;

  ForestAnim hugohitlog;
  ForestAnim hugohitlog_talk;
  ForestAnim catapult_fly;
  ForestAnim catapult_fall;
  ForestAnim catapult_airtalk;
  ForestAnim catapult_hang;
  ForestAnim catapult_hangspeak;
  ForestAnim hugo_lookrock;
  ForestAnim hit_rock;
  ForestAnim hugo_traphurt;

  oosFile *sync_start;
  oosFile *sync_rock;
  oosFile *sync_dieonce;
  oosFile *sync_trap;
  oosFile *sync_lastlife;
  oosFile *sync_catapult_talktop;
  oosFile *sync_catapult_hang;
  oosFile *sync_hitlog;
  oosFile *sync_gameover;
  oosFile *sync_levelcompleted;

  ForestAnim cave_talks;
  ForestAnim cave_climbs;
  ForestAnim cave_first_rope;
  ForestAnim cave_second_rope;
  ForestAnim cave_third_rope;
  ForestAnim cave_scylla_leaves;
  ForestAnim cave_scylla_bird;
  ForestAnim cave_scylla_ropes;
  ForestAnim cave_scylla_spring;
  ForestAnim cave_family_cage;
  ForestAnim cave_hugo_puff_first;
  ForestAnim cave_hugo_puff_second;
  ForestAnim cave_hugo_puff_third;
  ForestAnim cave_hugo_spring;
  ForestAnim cave_happy;
  cgfFile *cave_hugo_sprite;
  cgfFile *cave_score_font;
} GameTextures;

typedef struct {
  ForestSound speak_start;
  ForestSound speak_rock;
  ForestSound speak_dieonce;
  ForestSound speak_trap;
  ForestSound speak_lastlife;
  ForestSound speak_catapult_up;
  ForestSound speak_catapult_hit;
  ForestSound speak_catapult_talktop;
  ForestSound speak_catapult_down;
  ForestSound speak_catapult_hang;
  ForestSound speak_hitlog;
  ForestSound speak_gameover;
  ForestSound speak_levelcompleted;

  ForestSound sfx_bg_atmosphere;
  ForestSound sfx_lightning_warning;
  ForestSound sfx_hugo_knock;
  ForestSound sfx_hugo_hittrap;
  ForestSound sfx_hugo_launch;
  ForestSound sfx_sack_normal;
  ForestSound sfx_sack_bonus;
  ForestSound sfx_tree_swush;
  ForestSound sfx_hugo_hitlog;
  ForestSound sfx_catapult_eject;
  ForestSound sfx_birds;
  ForestSound sfx_hugo_screenklir;
  ForestSound sfx_hugo_crash;
  ForestSound sfx_hugo_hangstart;
  ForestSound sfx_hugo_hang;
  ForestSound sfx_hugo_walk[5];

  ForestSound cave_her_er_vi;
  ForestSound cave_trappe_snak;
  ForestSound cave_nu_kommer_jeg;
  ForestSound cave_afskylia_snak;
  ForestSound cave_hugo_katapult;
  ForestSound cave_hugo_skyd_ud;
  ForestSound cave_afskylia_skyd_ud;
  ForestSound cave_hugoline_tak;
  ForestSound cave_fodtrin1;
  ForestSound cave_fodtrin2;
  ForestSound cave_hiv_i_reb;
  ForestSound cave_fjeder;
  ForestSound cave_pre_puf;
  ForestSound cave_puf;
  ForestSound cave_tast_trykket;
  ForestSound cave_pre_fanfare;
  ForestSound cave_fanfare;
  ForestSound cave_fugle_skrig;
  ForestSound cave_trappe_grin;
  ForestSound cave_skrig;
  ForestSound cave_score_counter;
} GameAudio;

typedef enum {
  FOREST_STATE_NONE,
  FOREST_STATE_INSTRUCTIONS,
  FOREST_STATE_FOREST,
  FOREST_STATE_CAVE,
  FOREST_STATE_END
} GameState;

typedef struct {
  bool audio_played[4];
  double audio_start_time[4];
  double start_time;
} StateMetadata;

typedef struct {
  bool key_up;
  bool key_down;
  bool key_start;
  bool cave_rope_1_pressed;
  bool cave_rope_2_pressed;
  bool cave_rope_3_pressed;
  bool debug_toggle;
} InputState;

extern GameTextures textures;
extern GameAudio audio;
extern SDL_Surface *forest_screen;

#endif /* FOREST_TYPES_HPP */
