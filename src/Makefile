CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -Wall -Werror -Wextra  -fprofile-arcs -ftest-coverage
SRC = s21_matrix.c
OBJS = $(SRC:.c=.o)
OS := $(shell uname -s)

ifeq ($(OS),Linux)
  LIBS =  -lcheck -lm -lrt -lpthread -lsubunit
  LEAKS = CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --read-var-info=yes ./unit_test
  REPORT = xdg-open ./report/index.html
else ifeq ($(OS),Darwin)
  LIBS = -lcheck -lm -lpthread
  LEAKS = leaks -atExit -- ./unit_test
  REPORT = open ./report/index.html
endif

.PHONY: test rt

all: s21_matrix.a

s21_matrix.a: $(OBJS)
	ar rcs s21_matrix.a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rt: clean test leaks

test: clean c_format s21_matrix.a s21_matrix_test.o 
	clear
	$(CC) $(CFLAGS) s21_matrix_test.o s21_matrix.a -o unit_test $(LIBS)
	./unit_test

s21_matrix_test.o: 
	$(CC) $(CFLAGS) -c s21_matrix_test.c -o s21_matrix_test.o

gcov_report: clean c_format s21_matrix_test.o $(SRC)
	$(CC) $(GCOVFLAGS) -c $(SRC) 
	ar rcs s21_matrix.a $(OBJS)
	$(CC) $(GCOVFLAGS) -c s21_matrix_test.c -o s21_matrix_test.o
	$(CC) $(GCOVFLAGS) s21_matrix_test.o s21_matrix.a -o gcov_unit_test $(LIBS)
	./gcov_unit_test
	lcov -t "test" -o test.info --no-external -c -d .
	lcov --remove test.info "*s21_matrix_test.c*" -o test.info 
	genhtml -o report/ test.info
	$(REPORT)
	make clean_without_report

c_format:
	clang-format -style=Google -i *.c *.h

leaks: 
	$(LEAKS)

clean_without_report: 
	rm -f  *.o *.gcno *.gcov *.gcda gcov_unit_test output.txt *.info *.a main_test unit_test s21_matrix

clean: clean_without_report
	rm -rf report gcov_unit_test
