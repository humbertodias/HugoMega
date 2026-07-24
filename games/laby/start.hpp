#include "step1.hpp"

Uint32 labyStart(Uint32 &score, Uint32 gameMode, Uint32 playerMode, SDL_Window *window, SDL_Surface *screen)
{
	Uint32 st = 1;
	rawFile introPic(getFullPath("LabyrinthData/gfx/INTROPIC.RAW"));
	cgfFile hugoSync(getFullPath("LabyrinthData/gfx/Hugosync.cgf"));
	wavFile introSpeak(getFullPath("LabyrinthData/Sfx/001-01.wav"));
	oosFile introSync(getFullPath("LabyrinthData/Sync/001-01.oos"));
	tilFile labyBack1(getFullPath("LabyrinthData/gfx/Baggrund_m.Sand4.til"));
	tilFile labyMap(getFullPath("LabyrinthData/gfx/ArcadeMap.til"));
	std::string pathMapArrows;
	if (!gameMode)
	{
		pathMapArrows = "LabyrinthData/gfx/MapArrows.cgf";
	}
	else
	{
		pathMapArrows = "LabyrinthData/gfx/ArcadeMapArrows.cgf";
	}
	cgfFile mapArrows(getFullPath(pathMapArrows));
	cgfFile hugoWalksRight(getFullPath("LabyrinthData/gfx/HugoWalksRight2.cgf"));
	cgfFile hugoWalksLeft(getFullPath("LabyrinthData/gfx/HugoWalksLeft2.cgf"));
	cgfFile hugoJumpsRight(getFullPath("LabyrinthData/gfx/HugoJumpsRight.cgf"));
	cgfFile hugoJumpsLeft(getFullPath("LabyrinthData/gfx/HugoJumpsLeft.cgf"));
	wavFile runSound(getFullPath("LabyrinthData/Sfx/Run2-lp.wav"));

	st = st * introPic.getStatus();
	st = st * hugoSync.getStatus();
	st = st * introSpeak.getStatus();
	st = st * introSync.getStatus();
	st = st * labyBack1.getStatus();
	st = st * labyMap.getStatus();
	st = st * mapArrows.getStatus();
	st = st * hugoWalksRight.getStatus();
	st = st * hugoWalksLeft.getStatus();
	st = st * hugoJumpsRight.getStatus();
	st = st * hugoJumpsLeft.getStatus();
	st = st * runSound.getStatus();
	if (!st)
	{
		return 1;
	}

	/* 1) Intro speak + lip sync */
	introSync.playOos(introSpeak, hugoSync, -0x42, -0x10, introPic, window, screen);

	/* 2) Map overview, then 3) side-scroller play (hugo-games step1) */
	if (!labyStep1(score, gameMode, playerMode, window, screen, labyBack1, labyMap, mapArrows,
				   hugoWalksRight, hugoWalksLeft, hugoJumpsRight, hugoJumpsLeft, runSound))
	{
	}
	return 0;
}
