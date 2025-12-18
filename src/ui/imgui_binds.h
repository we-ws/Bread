#pragma once
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#define imgui_binds_h

#include <stdbool.h>

int Imgui_OpenGL_SDL3 (bool WindowStat, SDL_Window *Window, SDL_Event event);
