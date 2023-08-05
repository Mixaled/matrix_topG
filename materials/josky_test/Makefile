# Platform-specific behaviour
CC=gcc -Wall -Wextra -std=c11
GCOV_FLAGS= -fprofile-arcs -ftest-coverage

UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LINK_FLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	SYSFLAG=-D LINUX
endif 
ifeq ($(UNAME),Darwin)
	LINK_FLAGS=-lcheck -lm
	LEAK=CK_FORK=no leaks -quiet -atExit --
	SYSFLAG=-D APPLE
endif 

all: test_verdaqui test_rynotheast test_vasyan test_minella

clean:
	rm -f *.o
	rm -f */*.o
	rm -f *.out
	rm -f tests_vasyan/test.check.c
	rm -f s21_matrix.h
	rm -f s21_matrix.a

PURPLE=\033[0;35m
NC=\033[0m

test_ver: test_verdaqui
test_verdaqui: test_verdaqui.out
	@echo "${PURPLE}Running tests of verdaqui${NC}"
	./test_verdaqui.out || true

test_r: test_rynotheast
test_rynotheast: test_rynotheast.out
	@echo "${PURPLE}Running tests of rynotheast${NC}"
	./test_rynotheast.out || true

test_v: test_vasyan
test_vasyan: test_vasyan.out
	@echo "${PURPLE}Running tests of vasyan${NC}"
	./test_vasyan.out || true

test_m: test_minella
test_minella: test_minella.out
	@echo "${PURPLE}Running tests of minella${NC}"
	./test_minella.out || true

# Boilerplate
%.o: %.c
	$(CC) -c $^  -o $@

VERDAQUI_SOURCES=$(wildcard ./tests_verdaqui/*.c) $(wildcard ./tests_verdaqui/*.h)
VERDAQUI_C_SOURCES=$(filter %.c,$(VERDAQUI_SOURCES))
VERDAQUI_H_SOURCES=$(filter %.h,$(VERDAQUI_SOURCES))
VERDAQUI_OBJ_FILES=$(VERDAQUI_C_SOURCES:.c=.o)

test_verdaqui.out: ${VERDAQUI_H_SOURCES} ${VERDAQUI_OBJ_FILES} s21_matrix.a
	${CC} ${VERDAQUI_OBJ_FILES} s21_matrix.a  ${LINK_FLAGS} -o test_verdaqui.out

test_rynotheast.out: s21_matrix.a tests_rynotheast/SUITE_main.c
	gcc $(CFLAGS) tests_rynotheast/SUITE_main.c s21_matrix.a ${LINK_FLAGS} -o test_rynotheast.out

tests_vasyan/test.check.c: tests_vasyan/tests_s21_matrix.check
	checkmk clean_mode=1 tests_vasyan/tests_s21_matrix.check > tests_vasyan/test.check.c

test_vasyan.out: s21_matrix.a tests_vasyan/test.check.c
	${CC} $(CFLAGS) tests_vasyan/test.check.c s21_matrix.a ${LINK_FLAGS} -g -o test_vasyan.out

test_minella.out: s21_matrix.a tests_minella.c
	gcc $(CFLAGS) tests_minella.c s21_matrix.a ${LINK_FLAGS} -o test_minella.out