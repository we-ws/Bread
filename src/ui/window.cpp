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
  
  window = SDL_CreateWindow(
      "Bread",
      1280,
      720,
      SDL_WINDOW_RESIZABLE
    );

  SDL_SetWindowMinimumSize(window, 800, 600);

  //std::cout<<WinDone<<"\n";

  while (!WinDone) {
  
  WINDOW_DATA_THREAD = SDL_CreateThread(WindowDebug, "WindowDbg", NULL);
  
 // while (!WinDone) {

  
  system("cls");
  

   while( SDL_PollEvent(&WinEvent)) {
    
    if (WinEvent.type == SDL_EVENT_QUIT){
      WinDone = true;
      //std::cout<<WinDone<<"\n";
      return 0;;
    }
   }
  }

  system("cls");
  
  SDL_DestroyWindow(window);

  SDL_Quit();

  //std::cout<<WinDone<<"\n";


  
  return 0;
}
