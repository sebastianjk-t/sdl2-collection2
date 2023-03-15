CC = clang++
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
SRC_FILES = *.cpp
BUILD_DIR = .
OBJ_NAME = tetris

run: compile
	@$(BUILD_DIR)/$(OBJ_NAME)

compile:
	@$(CC) $(COMPILER_FLAGS) $(SDL_FLAGS) $(SRC_FILES) -o $(OBJ_NAME)
