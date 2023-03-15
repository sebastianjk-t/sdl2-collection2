CC = clang++
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
SRC_DIR = src
SRC_FILES = $(SRC_DIR)/*.cpp
BUILD_DIR = build/debug
OBJ_NAME = play

run: compile
	@./build/debug/play

compile:
	@$(CC) $(COMPILER_FLAGS) $(SDL_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)