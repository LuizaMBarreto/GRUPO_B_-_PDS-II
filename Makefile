CC = g++
CFLAGS = -std=c++11 -Wall -Iinclude

all: test

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
	rm -f build/test_runner build/*.o *.gcda *.gcno src/*.gcda src/*.gcno tests/*.gcda tests/*.gcno

