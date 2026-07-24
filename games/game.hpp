#ifndef GAMES_GAME_HPP
#define GAMES_GAME_HPP

#include <string>
#include <SDL2/SDL.h>
/* font.hpp / localfolder.hpp: included by hugomain before menu; no include guards. */

using GameStartFn = Uint32 (*)(Uint32 &score, Uint32 gameMode, Uint32 playerMode,
                               SDL_Window *window, SDL_Surface *screen);

#define GAME_FILM_SLOTS 21

/* Fallback when a film slot has no game or assets failed to load. */
static Uint32 unavailableStart(const std::string &gameName, Uint32 &score,
                               Uint32 gameMode, Uint32 playerMode,
                               SDL_Window *window, SDL_Surface *screen)
{
	(void)score;
	(void)gameMode;
	(void)playerMode;

	palFile menuPal(getFullPath("MenuData/mainpal.pal"));
	fontText menuFont(getFullPath("MenuData/MenuFont.cgf"),
	                  getFullPath("MenuData/charmapmenu.txt"), menuPal);
	menuFont.setNullPosX();
	std::string title = gameName.empty() ? std::string("Unknown") : gameName;
	std::string subtitle = "Coming soon";
	std::string hint = "Press Enter or Esc";

	int exitFlag = 0;
	while (!exitFlag)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				exitFlag = 1;
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE ||
				    e.key.keysym.sym == SDLK_RETURN ||
				    e.key.keysym.sym == SDLK_KP_ENTER)
					exitFlag = 1;
			}
		}

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		if (menuFont.getStatus())
		{
			Uint32 tw = menuFont.widthText(title);
			Uint32 sw = menuFont.widthText(subtitle);
			Uint32 hw = menuFont.widthText(hint);
			menuFont.printText(title, (640 - tw) / 2, 180, screen, 1, 1);
			menuFont.printText(subtitle, (640 - sw) / 2, 240, screen, 1, 1);
			menuFont.printText(hint, (640 - hw) / 2, 320, screen, 1, 1);
		}
		SDL_UpdateWindowSurface(window);
		SDL_Delay(16);
	}
	return 0;
}

#endif /* GAMES_GAME_HPP */
