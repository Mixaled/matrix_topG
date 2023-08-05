CFLAGS=-Wall -Werror -Wextra
GCOV=-fprofile-arcs -ftest-coverage
OBJECTS=s21_matrix.o
SOURCES=s21_matrix.c

UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LIBS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAKS_IN = valgrind --leak-check=full
endif 
ifeq ($(UNAME),Darwin)
	LIBS=-lcheck -lm
	LEAKS_IN = leaks -atExit --
endif 

all: main
main: clean s21_matrix.a test clang_format gcov_report

s21_matrix.a:  $(SOURCES) s21_matrix.h
	gcc $(CFLAGS) -c $(SOURCES)  
	ar rcs s21_matrix.a $(OBJECTS)

josky_test/s21_matrix.a: s21_matrix.a
	cp s21_matrix.a josky_test/
	
josky_test/s21_matrix.h: s21_matrix.h
	cp s21_matrix.h josky_test/

test_j: josky_test/s21_matrix.a josky_test/s21_matrix.h
	cd josky_test/ && make all

test: s21_matrix.a
	gcc $(CFLAGS) -g s21_matrix_test.c s21_matrix.a $(LIBS) -o test 
	./test

leaks: clean
	gcc $(CFLAGS) -c s21_matrix.c
	ar rcs s21_matrix.a s21_matrix.o
	gcc -Wall -Werror smartass.c s21_matrix.a -o smartass
	$(LEAKS_IN) ./smartass

gcov_report: s21_matrix.a
	gcc $(CFLAGS) $(GCOV) s21_matrix_test.c $(LIBS) $(SOURCES) -o GcovReport
	./GcovReport
	lcov -t "GcovReport" -o GcovReport.info -c -d .
	genhtml -o report GcovReport.info 

clean:
	rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./math_o ./test ./smartass
	cd josky_test && make clean

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

clang_formating:
	clang-format --style=google -i *.c *.h

rebuild: clean all


