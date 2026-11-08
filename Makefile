CC = g++
CFLAGS = -std=c++11 -Wall -Iinclude
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: test

game:
	mkdir -p build
	$(CC) $(CFLAGS) src/*.cpp src/interface/*.cpp -o build/rpg_game $(SFML_FLAGS)

run: game
	./build/rpg_game

terminal:
	mkdir -p build
	$(CC) $(CFLAGS) src/*.cpp src/terminal/*.cpp -o build/rpg_terminal
	./build/rpg_terminal

test:
	mkdir -p build
	$(CC) $(CFLAGS) src/*.cpp tests/*.cpp -o build/test_runner
	./build/test_runner

coverage:
	mkdir -p build
	$(CC) $(CFLAGS) --coverage src/*.cpp tests/*.cpp -o build/test_runner
	./build/test_runner
	gcovr -r . --filter 'src/'

clean:
	rm -f build/test_runner build/rpg_game build/*.o *.gcda *.gcno src/*.gcda src/*.gcno tests/*.gcda tests/*.gcno

