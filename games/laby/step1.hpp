void labyMapLoad(SDL_Surface *screen, tilFile &labyMap, cgfFile &mapArrows, Uint32 mapX0, Uint32 mapY0,
				Uint32 mapX, Uint32 mapY, Uint32 gameMode, Uint32 numArrow)
{
	labyMap.loadFrame(gameMode, screen);
	mapArrows.draw(numArrow % 4, (mapX - mapX0) * 5, (mapY - mapY0) * 5, 1, screen, 1, 0);
}

void labyShowMap(SDL_Window *window, SDL_Surface *screen, Uint32 gameMode,
				tilFile &labyMap, cgfFile &mapArrows)
{
	Uint32 mapX0, mapY0;
	if (!gameMode)
	{
		mapX0 = 0x13;
		mapY0 = 0x23;
	}
	else
	{
		mapX0 = 0x17;
		mapY0 = 0x2A;
	}
	Uint32 mapX = mapX0, mapY = mapY0;
	labyMapLoad(screen, labyMap, mapArrows, mapX0, mapY0, mapX, mapY, gameMode, 0);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
}

Uint32 labyPlay(Uint32 &score, Uint32 gameMode, Uint32 playerMode, SDL_Window *window,
				tilFile &labyBack1, cgfFile &hugoWalksRight, cgfFile &hugoWalksLeft,
				cgfFile &hugoJumpsRight, cgfFile &hugoJumpsLeft, wavFile &runSound)
{
	(void)score;
	(void)gameMode;
	(void)playerMode;

	SDL_Surface *screen = NULL;
	SDL_Event e;
	Uint32 timer = SDL_GetTicks();
	Uint32 timeWalk = SDL_GetTicks();
	Uint32 backFrame = 0;
	Uint32 walkFrame = 0;
	Uint32 facingLeft = 0;
	Uint32 labyExit = 0;
	cgfFile *hugoWalk = &hugoWalksRight;
	Uint32 backFrames = labyBack1.getNum();
	if (backFrames == 0)
	{
		return 1;
	}

	runSound.clearAudio();
	runSound.loadAudio();
	runSound.playAudio();
	timeWalk = SDL_GetTicks();
	while (SDL_PollEvent(&e))
	{
	}

	while (!labyExit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					labyExit = 1;
				}
				else if (((e.key.keysym.scancode == SDL_SCANCODE_KP_4) ||
						  (e.key.keysym.scancode == SDL_SCANCODE_LEFT)) &&
						 (facingLeft == 0))
				{
					hugoWalk = &hugoWalksLeft;
					facingLeft = 1;
					timer = SDL_GetTicks();
					runSound.stopAudio();
					runSound.clearAudio();
					for (Uint32 i = 0; i < hugoJumpsLeft.getNum(); ++i)
					{
						screen = SDL_GetWindowSurface(window);
						labyBack1.loadFrame(backFrame, screen);
						hugoJumpsLeft.draw(i, 0, 0, 1, screen, 1, 0);
						SDL_UpdateWindowSurface(window);
						backFrame = (backFrame + 1) % backFrames;
						while (SDL_GetTicks() - timer < 60)
						{
						}
						timer = SDL_GetTicks();
					}
					while (SDL_PollEvent(&e))
					{
					}
					runSound.clearAudio();
					runSound.loadAudio();
					runSound.playAudio();
					timeWalk = SDL_GetTicks();
				}
				else if (((e.key.keysym.scancode == SDL_SCANCODE_KP_6) ||
						  (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)) &&
						 (facingLeft == 1))
				{
					hugoWalk = &hugoWalksRight;
					facingLeft = 0;
					timer = SDL_GetTicks();
					runSound.stopAudio();
					runSound.clearAudio();
					for (Uint32 i = 0; i < hugoJumpsRight.getNum(); ++i)
					{
						screen = SDL_GetWindowSurface(window);
						labyBack1.loadFrame(backFrame, screen);
						hugoJumpsRight.draw(i, 0, 0, 1, screen, 1, 0);
						SDL_UpdateWindowSurface(window);
						backFrame = (backFrame + 1) % backFrames;
						while (SDL_GetTicks() - timer < 60)
						{
						}
						timer = SDL_GetTicks();
					}
					while (SDL_PollEvent(&e))
					{
					}
					runSound.clearAudio();
					runSound.loadAudio();
					runSound.playAudio();
					timeWalk = SDL_GetTicks();
				}
			}
		}

		screen = SDL_GetWindowSurface(window);
		labyBack1.loadFrame(backFrame, screen);
		hugoWalk->draw(walkFrame, 0, 0, 1, screen, 1, 0);
		SDL_UpdateWindowSurface(window);
		backFrame = (backFrame + 1) % backFrames;
		walkFrame = (walkFrame + 1) % hugoWalk->getNum();

		if (SDL_GetTicks() - timeWalk > runSound.getTimeLength())
		{
			runSound.clearAudio();
			runSound.loadAudio();
			timeWalk = SDL_GetTicks();
		}
		while (SDL_GetTicks() - timer < 60)
		{
		}
		timer = SDL_GetTicks();
		if (SDL_GetTicks() - timeWalk > runSound.getTimeLength())
		{
			runSound.clearAudio();
			runSound.loadAudio();
			timeWalk = SDL_GetTicks();
		}
	}

	runSound.stopAudio();
	runSound.clearAudio();
	return 0;
}

Uint32 labyStep1(Uint32 &score, Uint32 gameMode, Uint32 playerMode, SDL_Window *window, SDL_Surface *screen,
				tilFile &labyBack1, tilFile &labyMap, cgfFile &mapArrows,
				cgfFile &hugoWalksRight, cgfFile &hugoWalksLeft,
				cgfFile &hugoJumpsRight, cgfFile &hugoJumpsLeft, wavFile &runSound)
{
	labyShowMap(window, screen, gameMode, labyMap, mapArrows);
	return labyPlay(score, gameMode, playerMode, window, labyBack1,
					hugoWalksRight, hugoWalksLeft, hugoJumpsRight, hugoJumpsLeft, runSound);
}
