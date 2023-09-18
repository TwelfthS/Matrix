all: s21_matrix.a

s21_matrix.a:
	gcc -c s21_matrix.c
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

test:
	gcc s21_matrix.c test.c -lcheck -o test
	-./test
	rm -rf test

gcov_report:
	gcc -c --coverage s21_matrix.c
	gcc -c test.c
	gcc s21_matrix.o test.o -o test -lcheck -lgcov
	-./test
	lcov -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

style:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

clean:
	rm -rf *.a *.o *.gcno *.gcda *.gcov *.info test report main