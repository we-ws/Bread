#include "GL/gl.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_video.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "window.h"


#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_sdl3.h"
#include <SDL3/SDL.h>
#include <cfloat>
#include <cstdlib>
#include <d3d11.h>
#include <stdio.h>



int Imgui_OpenGL_SDL3 (bool WindowStat, SDL_Window *Window, SDL_Event event) {
  const char* GLSL_VERSION;
    
  #if defined (IMGUI_IMPL_OPENGL_ES3)
    GLSL_VERSION = "#version 300 es";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  #endif

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  printf("Line 35 in Imgui_binds\n");
 // SDL_GLContext GL_Context = SDL_GL_CreateContext(Window);

  SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

  Window = SDL_CreateWindow(
      "Bread",
      1280,
      720,
      flags
    );

  SDL_GLContext GL_Context = SDL_GL_CreateContext(Window);

  
    
  if (Window == nullptr) {
    printf("Window Creation Failure %s", SDL_GetError());
    return 1;
  }
//  SDL_GLContext GL_Context = SDL_GL_CreateContext(Window);

  if (GL_Context == nullptr) {
    printf("[E001] Error SDL OpenGL Context: %s", SDL_GetError());
    return 1;
  }

  printf("TEST1\n");

  SDL_GL_MakeCurrent(Window, GL_Context);
  SDL_GL_SetSwapInterval(1);
  SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(Window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |=  ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  int Window_Width;
  int Window_Height;

  ImVec2 MinSizeLWindow =  ImVec2(400,Window_Height); 
  
  ImGui_ImplSDL3_InitForOpenGL(Window, GL_Context);
  ImGui_ImplOpenGL3_Init(GLSL_VERSION);
  printf("TEST2\n");


  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  printf("TEST3\n");
  while (!WindowStat) {
 //   system("cls");
 //   printf("Waiting Winstat to update\n");

    while (SDL_PollEvent(&event)) {
 //     system("cls");
 //     printf("Waiting to poll event\n");

      ImGui_ImplSDL3_ProcessEvent(&event);
      if (event.type == SDL_EVENT_QUIT) {
        WindowStat = true;        
        }
    }

//NewFrame
    SDL_GetWindowSize(Window, &Window_Width, &Window_Height);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();



    static float f = 0.0f;
    static int counter = 0;

    ImGui::SetNextWindowPos(ImVec2(0,0),ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2( (Window_Width / 3.5),(Window_Height / 2.0)));
    //ImGui::SetNextWindowSizeConstraints(MinSizeLWindow,  ImVec2(FLT_MAX,Window_Height));
    
    ImGui::Begin("Hello, world!",nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)    
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
 //   ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
    
      

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Window Width: %i, Window Height: %i", Window_Width, Window_Height );
    
    ImVec2 GuiPos = ImGui::GetWindowPos();
    ImGui::Text("Window Pos %.1f %.1f",GuiPos.x,GuiPos.y);
    
    ImGui::End();

//EndNewFrame

  
  
  ImGui::Begin("TEST WINDOW 2");
  

  ImGui::End();

  ImGui::Render();

  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(Window);

  }

 ImGui_ImplOpenGL3_Shutdown();
 ImGui_ImplSDL3_Shutdown();
 ImGui::DestroyContext();

 SDL_GL_DestroyContext(GL_Context);

 SDL_DestroyWindow(Window);
 
  
 printf("Reached EOF without errors for File Imgui_Binds.cpp");
  return 0;
}
