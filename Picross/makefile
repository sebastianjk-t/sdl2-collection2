CC = clang++
FLAGS = -std=c++11 -Wall
SDL = `sdl2-config --cflags --libs` -lSDL2_ttf
NAME = picross

run: compile
	@./$(NAME)

compile:
	@$(CC) $(FLAGS) $(SDL) *.cpp -o $(NAME)