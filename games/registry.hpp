#ifndef GAMES_REGISTRY_HPP
#define GAMES_REGISTRY_HPP

#include "game.hpp"
#include "laby/start.hpp"
#include "forest/start.hpp"

/*
 * Film-strip slot → start function.
 * Index matches MenuData/games.txt / menu numGame (0..20).
 * Add a new game: implement xxxStart, #include it here, set one slot below.
 */
static GameStartFn g_games[GAME_FILM_SLOTS] = {
	labyStart,   /*  0 Labyrinth */
	nullptr,     /*  1 Train */
	nullptr,     /*  2 Plane */
	forestStart, /*  3 Forest */
	nullptr,     /*  4 Mountain */
	nullptr,     /*  5 Mine */
	nullptr,     /*  6 Scuba */
	nullptr,     /*  7 Ice Cave */
	nullptr,     /*  8 Lumberjack */
	nullptr,     /*  9 Skateboard */
	nullptr,     /* 10 Balloon */
	nullptr,     /* 11 Cave */
	nullptr,     /* 12 Swamp */
	nullptr,     /* 13 Snowboard */
	nullptr,     /* 14 Motorcycle */
	nullptr,     /* 15 Parachute */
	nullptr,     /* 16 Sled */
	nullptr,     /* 17 Rock Climber */
	nullptr,     /* 18 Bridge */
	nullptr,     /* 19 Stones */
	nullptr,     /* 20 Wild River */
};

static Uint32 launchGame(Uint32 gameId, const std::string &gameName, Uint32 &score,
                         Uint32 gameMode, Uint32 playerMode,
                         SDL_Window *window, SDL_Surface *screen)
{
	if (gameId >= GAME_FILM_SLOTS || g_games[gameId] == nullptr)
		return unavailableStart(gameName, score, gameMode, playerMode, window, screen);

	Uint32 rc = g_games[gameId](score, gameMode, playerMode, window, screen);
	if (rc != 0)
		return unavailableStart(gameName, score, gameMode, playerMode, window, screen);
	return 0;
}

#endif /* GAMES_REGISTRY_HPP */
