CC = clang++
FLAGS = -std=c++11 -Wall
SDL = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
NAME = rayCaster

run: compile
	@./$(NAME)

compile:
	@$(CC) $(FLAGS) $(SDL) *.cpp -o $(NAME)
