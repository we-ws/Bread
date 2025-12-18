#include "window.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_thread.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>

#include "imgui_binds.h"

SDL_Window *window;
bool WinDone;
SDL_Event WinEvent;
int x_size, y_size;

SDL_Thread* WINDOW_DATA_THREAD;

int SDLCALL WindowDebug(void* data) {
  data = NULL;
  SDL_GetWindowSize(window, &x_size, &y_size);  
  std::cout<<"Window Memory Address: "<<window<<"\n"<<"Window Current Size: "<<"X: " <<x_size<<" "<<"Y: "<<y_size<<"\n";
  system("cls");

  SDL_Delay(50);
  return 0;
};

int MainW() {

  WinDone = false;
  
  SDL_Init(SDL_INIT_VIDEO);

  
  Imgui_OpenGL_SDL3(WinDone, window, WinEvent);
  
  SDL_Quit();
  return 0;
}
