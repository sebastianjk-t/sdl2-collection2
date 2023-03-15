CC = clang++
FLAGS = -std=c++11 -Wall -O0 -g
SDL = `sdl2-config --cflags --libs`
NAME = artificialLife

run: compile
	@./$(NAME)

compile:
	@$(CC) $(FLAGS) $(SDL) *.cpp -o $(NAME)