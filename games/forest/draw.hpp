#ifndef FOREST_DRAW_HPP
#define FOREST_DRAW_HPP

#include "types.hpp"

SDL_Surface *forest_screen;

int forest_anim_frame_count(ForestAnim *anim)
{
  return anim->end - anim->start + 1;
}

int forest_cgf_width(cgfFile *info)
{
  if (!info || !info->getStatus() || info->getNum() == 0)
    return 0;
  return (int)info->getWidth(0);
}

int forest_cgf_height(cgfFile *info)
{
  if (!info || !info->getStatus() || info->getNum() == 0)
    return 0;
  return (int)info->getHeight(0);
}

void forest_draw_rect_fill(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  int px, py, x0, y0, x1, y1;
  if (!forest_screen || w <= 0 || h <= 0)
    return;
  x0 = x < 0 ? 0 : x;
  y0 = y < 0 ? 0 : y;
  x1 = x + w;
  y1 = y + h;
  if (x1 > FOREST_SCREEN_WIDTH)
    x1 = FOREST_SCREEN_WIDTH;
  if (y1 > FOREST_SCREEN_HEIGHT)
    y1 = FOREST_SCREEN_HEIGHT;
  for (py = y0; py < y1; py++)
    for (px = x0; px < x1; px++)
      set_pixel_2x(forest_screen, (Uint32)px, (Uint32)py, r, g, b, a);
}

void forest_draw_rect_outline(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  forest_draw_rect_fill(x, y, w, 1, r, g, b, a);
  forest_draw_rect_fill(x, y + h - 1, w, 1, r, g, b, a);
  forest_draw_rect_fill(x, y, 1, h, r, g, b, a);
  forest_draw_rect_fill(x + w - 1, y, 1, h, r, g, b, a);
}

void forest_clear_screen(void)
{
  if (!forest_screen)
    return;
  SDL_FillRect(forest_screen, NULL, SDL_MapRGB(forest_screen->format, 0, 0, 0));
}

void forest_blit_surface(SDL_Surface *src, int x, int y)
{
  SDL_Rect dest;
  if (!src || !forest_screen)
    return;
  dest.x = x * 2;
  dest.y = y * 2;
  dest.w = src->w * 2;
  dest.h = src->h * 2;
  SDL_BlitScaled(src, NULL, forest_screen, &dest);
}

void forest_draw_anim_frame(ForestAnim *anim, int local_frame, int x, int y)
{
  int abs_frame;
  if (local_frame < 0 || local_frame >= forest_anim_frame_count(anim))
    return;
  abs_frame = anim->start + local_frame;
  if (anim->is_til)
  {
    (void)x;
    (void)y;
    if (anim->til && anim->til->getStatus())
      anim->til->loadFrame((Uint32)abs_frame, forest_screen);
  }
  else if (anim->cgf && anim->cgf->getStatus())
  {
    anim->cgf->drawAt((Uint32)abs_frame, x, y, 1, forest_screen, 1, 0);
  }
}

void forest_draw_anim_full(ForestAnim *anim, int local_frame)
{
  forest_draw_anim_frame(anim, local_frame, 0, 0);
}

void forest_draw_sync_cgf(ForestAnim *anim, oosFile *sync, int tick, int x, int y)
{
  int local;
  if (!sync || !sync->getStatus() || tick < 0 || (Uint32)tick >= sync->getSize())
    return;
  local = (int)sync->getSyncFrame((Uint32)tick) - 1;
  if (local < 0)
    local = 0;
  if (local >= forest_anim_frame_count(anim))
    local = forest_anim_frame_count(anim) - 1;
  if (anim->cgf && anim->cgf->getStatus())
    anim->cgf->drawAt((Uint32)(anim->start + local), x, y, 1, forest_screen, 1, 0);
}

void forest_draw_sync_til(ForestAnim *anim, oosFile *sync, int tick)
{
  int local;
  if (!sync || !sync->getStatus() || tick < 0 || (Uint32)tick >= sync->getSize())
    return;
  local = (int)sync->getSyncFrame((Uint32)tick) - 1;
  if (local < 0)
    local = 0;
  if (local >= forest_anim_frame_count(anim))
    local = forest_anim_frame_count(anim) - 1;
  if (anim->til && anim->til->getStatus())
    anim->til->loadFrame((Uint32)(anim->start + local), forest_screen);
}

#endif /* FOREST_DRAW_HPP */
