CXX := g++ -std=c++20
CC := gcc -std=c11
FLAGS := -Wall -Werror -Wextra

CINC := -I ./brick_game/ -I ./brick_game/tetris/
CXXINC := -I ./brick_game/ -I ./brick_game/snake/

OS=$(shell uname)
ifeq ($(OS), Linux)
	NCURSES_FLAGS := -lncursesw
	CHECK_FLAGS := -lcheck -lm -lsubunit
	GTEST_FLAGS := $(shell pkg-config --static --cflags --libs gtest)
else
	NCURSES_FLAGS := $(shell pkg-config --static --cflags --libs ncurses)
	CHECK_FLAGS := $(shell pkg-config --static --cflags --libs check)
	GTEST_FLAGS := $(shell pkg-config --static --cflags --libs gtest)
endif

BUILD_DIR := build
TESTS_DIR := tests
REPORT_DIR := report
DOXYGEN_DIR := doxygen
DIST_DIR := ../dist

TEST_SRCS := $(wildcard ./tests/snake/*.cc ./brick_game/*.c ./brick_game/snake/*.cc)
GUI_SRCS := $(wildcard ./gui/desktop/*.cc ./gui/desktop/*.h)

BRICK_GAME_CONSOLE := brick_game_console
BRICK_GAME_DESKTOP := brick_game_desktop


all: install

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

install: $(BUILD_DIR) | $(BUILD_DIR)/$(BRICK_GAME_CONSOLE) $(BUILD_DIR)/$(BRICK_GAME_DESKTOP)

uninstall: 
	rm -rf $(BUILD_DIR)/$(PROJECT)

run_console: $(BUILD_DIR)/$(BRICK_GAME_CONSOLE)
	$^

run_desktop: $(BUILD_DIR)/$(BRICK_GAME_DESKTOP)
	$^

$(BUILD_DIR)/$(BRICK_GAME_CONSOLE): $(BUILD_DIR)/snake.a $(BUILD_DIR)/tetris.a $(BUILD_DIR)/curses_utils.o $(BUILD_DIR)/snake_view.o $(BUILD_DIR)/tetris_view.o $(BUILD_DIR)/main.o
	$(CXX) $^ -o $@ $(NCURSES_FLAGS)

$(BUILD_DIR)/tetris.a: $(BUILD_DIR)/tetris.o $(BUILD_DIR)/common.o
	ar rc $(BUILD_DIR)/tetris.a $^
	ranlib $(BUILD_DIR)/tetris.a

$(BUILD_DIR)/tetris.o: ./brick_game/tetris/tetris.c
	$(CC) $(FLAGS) $(CINC) -c $< -o $@

$(BUILD_DIR)/tetris_view.o: gui/cli/tetris_view.c
	$(CC) $(FLAGS) $(CINC) -c $< -o $@

$(BUILD_DIR)/curses_utils.o: gui/cli/curses_utils.c
	$(CC) $(FLAGS) $(CINC) -c $< -o $@


$(BUILD_DIR)/snake.a: $(BUILD_DIR)/model.o $(BUILD_DIR)/common.o
	ar rc $(BUILD_DIR)/snake.a $^
	ranlib $(BUILD_DIR)/snake.a

$(BUILD_DIR)/model.o: brick_game/snake/model.cc
	$(CXX) $(FLAGS) $(CXXINC) -c $< -o $@

$(BUILD_DIR)/common.o: brick_game/common.c
	$(CC) $(FLAGS) $(CINC) -c $< -o $@

$(BUILD_DIR)/snake_view.o: gui/cli/snake_view.cc 
	$(CXX) $(FLAGS) $(CXXINC) -c $< -o $@

$(BUILD_DIR)/main.o: gui/cli/main.cc
	$(CXX) $(FLAGS) $(CINC) $(CXXINC) -c $< -o $@


$(BUILD_DIR)/$(BRICK_GAME_DESKTOP): $(BUILD_DIR)/snake.a $(BUILD_DIR)/tetris.a $(GUI_SRCS)
	cp CMakeLists.txt $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_CXX_COMPILER=g++ -DPROJECT_NAME=$(BRICK_GAME_DESKTOP) ..
	cd $(BUILD_DIR) && $(MAKE)

dvi:
	doxygen
	open doxygen/html/index.html

dist: clean
	mkdir $(DIST_DIR)
	cp -r ../src ../dist
	cp ../README.md ../dist
	cd ../dist && tar -czvf dist.tar.gz ./src
	rm -rf ../dist/src

# old test:
# $(CC) $(FLAGS) $(CINC) ./tests/tetris/*.c ./$(BUILD_DIR)/tetris.a -o $(BUILD_DIR)/test_tetris $(CHECK_FLAGS)
# ./$(BUILD_DIR)/test_tetris

tests: $(BUILD_DIR)
	$(CXX) $(FLAGS) $(CXXINC) ./tests/snake/*.cc ./$(BUILD_DIR)/snake.a -o $(BUILD_DIR)/test_snake $(GTEST_FLAGS)
	./$(BUILD_DIR)/test_snake

gcov_report: $(BUILD_DIR) | $(BUILD_DIR)/snake.a
	$(CXX) $(FLAGS) $(CXXINC) --coverage ./brick_game/snake/*.cc ./tests/snake/*.cc ./$(BUILD_DIR)/snake.a -o gcov $(GTEST_FLAGS)
	./gcov
	lcov --capture --directory . -o gcov.info --ignore-errors inconsistent
	genhtml -o report gcov.info
	rm -rf gcov* *.gcda *.gcno
	open report/index.html

format:
	make clean
	cp ../materials/linters/.clang-format .
	find . -type f \( -name "*.cc" -o -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -i
	rm -rf .clang-format
	find . -type f \( -name "*.cc" -o -name "*.c" -o -name "*.h" \) -print0 | xargs -0 cppcheck $(CINC) $(CXXINC) --check-config --enable=all --suppress=missingIncludeSystem {} +


mem: install
ifeq ($(OS), Linux)
	valgrind --tool=memcheck --leak-check=yes $(BUILD_DIR)/$(BRICK_GAME_CONSOLE)
else
	leaks -atExit -- ./$(BUILD_DIR)/$(BRICK_GAME_CONSOLE)
# leaks -atExit -- $(BUILD_DIR)/$(BRICK_GAME_DESKTOP)
endif

build_dir:
	mkdir -p $(BUILD_DIR)

dist_dir:
	mkdir -p $(DIST_DIR)

debug:
	FLAGS += -g
	make install
	gdb ./$(BUILD_DIR)/$(PROJECT)

#install-sanitized : tetris.a
#$(CC) $(FLAGS) $(PROJECT).c $(GUI) $(BUILD_DIR)/tetris.a -o $(BUILD_DIR)/$(PROJECT) $(NCURSES_FLAGS) -fsanitize=address

.PHONY: install uninstall dvi dist test gcov_report clean

clean:
	rm -rf $(BUILD_DIR) $(REPORT_DIR) $(DOXYGEN_DIR) $(DIST_DIR)
	rm -rf .clang-format
	rm -rf *.info *.gcda *.gcno