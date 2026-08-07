#include "config.hpp"
#include "types.hpp"
#include "draw.hpp"
#include "audio.hpp"
#include "state.hpp"
#include "files.hpp"
#include "forest.hpp"
#include "cave.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>

static GameState forest_current_state;
static StateMetadata forest_loop_metadata;
static Uint8 forest_exit_flag = 0;

static void forest_read_input(SDL_Event *e, InputState *input)
{
	if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.scancode == SDL_SCANCODE_F1)
			input->debug_toggle = true;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_3 || e->key.keysym.scancode == SDL_SCANCODE_3)
			input->cave_rope_1_pressed = true;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_6 || e->key.keysym.scancode == SDL_SCANCODE_6)
			input->cave_rope_2_pressed = true;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_9 || e->key.keysym.scancode == SDL_SCANCODE_9)
			input->cave_rope_3_pressed = true;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_2 || e->key.keysym.scancode == SDL_SCANCODE_UP)
			input->key_up = true;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_8 || e->key.keysym.scancode == SDL_SCANCODE_DOWN)
			input->key_down = true;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_5 || e->key.keysym.scancode == SDL_SCANCODE_5)
			input->key_start = true;
	}
	else if (e->type == SDL_KEYUP)
	{
		if (e->key.keysym.scancode == SDL_SCANCODE_KP_3 || e->key.keysym.scancode == SDL_SCANCODE_3)
			input->cave_rope_1_pressed = false;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_6 || e->key.keysym.scancode == SDL_SCANCODE_6)
			input->cave_rope_2_pressed = false;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_9 || e->key.keysym.scancode == SDL_SCANCODE_9)
			input->cave_rope_3_pressed = false;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_2 || e->key.keysym.scancode == SDL_SCANCODE_UP)
			input->key_up = false;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_8 || e->key.keysym.scancode == SDL_SCANCODE_DOWN)
			input->key_down = false;
		else if (e->key.keysym.scancode == SDL_SCANCODE_KP_5 || e->key.keysym.scancode == SDL_SCANCODE_5)
			input->key_start = false;
	}
}

static void forest_game_loop(SDL_Window *window, SDL_Surface *screen)
{
	InputState input_state = {};
	SDL_Event e;

	forest_current_state = FOREST_STATE_FOREST;
	reset_state(&forest_loop_metadata);
	srand((unsigned int)time(NULL));
	on_enter_forest();

	while (!forest_exit_flag && forest_current_state != FOREST_STATE_END)
	{
		input_state.debug_toggle = false;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				forest_exit_flag = 1;
			else if (e.type == SDL_KEYDOWN &&
			         e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				forest_exit_flag = 1;
			else
				forest_read_input(&e, &input_state);
		}

		GameState new_state = FOREST_STATE_NONE;
		if (forest_current_state == FOREST_STATE_FOREST)
			new_state = process_forest(input_state);
		else if (forest_current_state == FOREST_STATE_CAVE)
			new_state = process_cave(input_state);

		if (new_state != FOREST_STATE_NONE)
		{
			if (forest_current_state == FOREST_STATE_FOREST && new_state == FOREST_STATE_CAVE)
				set_cave_score(get_forest_score());

			forest_current_state = new_state;
			reset_state(&forest_loop_metadata);

			if (forest_current_state == FOREST_STATE_FOREST)
				on_enter_forest();
			else if (forest_current_state == FOREST_STATE_CAVE)
				on_enter_cave();
		}

		forest_screen = SDL_GetWindowSurface(window);
		if (!forest_screen)
			forest_screen = screen;
		forest_clear_screen();

		if (forest_current_state == FOREST_STATE_FOREST)
			render_forest();
		else if (forest_current_state == FOREST_STATE_CAVE)
			render_cave();

		SDL_UpdateWindowSurface(window);
		SDL_Delay(33);
	}
}

Uint32 forestStart(Uint32 &score, Uint32 gameMode, Uint32 playerMode, SDL_Window *window, SDL_Surface *screen)
{
	(void)gameMode;
	(void)playerMode;

	forest_exit_flag = 0;
	if (ForestOpenFiles())
	{
		ForestUnloadFiles();
		return 2;
	}

	if (FOREST_SOUND_READY(audio.sfx_bg_atmosphere))
		forest_play_loop(&audio.sfx_bg_atmosphere);

	forest_game_loop(window, screen);
	forest_pause_all();

	score = (Uint32)get_forest_score();
	ForestUnloadFiles();
	return 0;
}
