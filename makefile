all:
	g++ src/*.cpp src/ui/*.cpp src/ui/*.h imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/backends/imgui_impl_sdl3.cpp imgui/backends/imgui_impl_dx11.cpp -Iimgui -Iimgui/backends -lSDL3 -ld3d11 -ldxgi -ld3dcompiler -o Test.exe
