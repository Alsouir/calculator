CC=gcc
CFLAGS= -Wall -Werror -Wextra -g -std=c11 
# -fsanitize=address  -lgcov
CCTEST:= gcc -ftest-coverage -fprofile-arcs 

TARGET:=Calculator

all: clean install

*/%.o: */%.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: */%.c 
	$(CCTEST) $(CFLAGS) -c $< -o $@

smart_calc.a: Calc_C/SmartCalc_C.o Calc_C/stack.o Calc_C/check.o Calc_C/deposit.o Calc_C/credit.o
	@ar -src $@ Calc_C/SmartCalc_C.o Calc_C/stack.o Calc_C/check.o Calc_C/deposit.o Calc_C/credit.o

html_smart_calc.a: SmartCalc_C.o stack.o check.o deposit.o credit.o
	@ar rc $@ SmartCalc_C.o stack.o check.o deposit.o credit.o

test: Test/tests.o smart_calc.a
ifeq ($(shell uname),Linux)          
	$(CC) Test/tests.o smart_calc.a -o tests -lcheck -lm -lsubunit
	./tests
else
	$(CC) Test/tests.o smart_calc.a -o tests -lcheck  -lm
	./tests
endif

html_test:  Test/tests.o html_smart_calc.a
ifeq ($(shell uname),Linux)   
	$(CCTEST)  Test/tests.o html_smart_calc.a -o tests -lcheck -lm -lsubunit 
else
	$(CCTEST)  Test/tests.o html_smart_calc.a -o tests -lcheck  -lm 
endif

install: uninstall
	@mkdir -p build
	@cd CalculatorQT && qmake && make && make clean && rm -rf Makefile && mv  $(TARGET) ../build
	@cp -R build/$(TARGET) ~/$(TARGET)
	@cd build && ./$(TARGET)

open: 
	@cd build && ./$(TARGET)

uninstall:
	@rm -rf build/$(TARGET)
	@rm -rf ~/$(TARGET)

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p dist
	@cp -R build/$(TARGET) dist
	@cp ../README_RUS.md dist && cp ../README.md dist
	@cd dist && tar cvzf $(TARGET).tgz *
	@cd dist && rm -rf build/$(TARGET) $(TARGET) README.md README_RUS.md


gcov_report: clean html_test
	./tests
	lcov -t "tests" -o fizzbuzz.info -c -d .
	genhtml -o report fizzbuzz.info
	@open report/index.html

style:
	@clang-format -i Calc_C/*.c Calc_C/*.h Test/*.c CalculatorQT/*.cpp CalculatorQT/*.h CalculatorQT/*.ui

valgrind: clean test
	valgrind --tool=memcheck --leak-check=yes  ./tests

clean:
	rm -rf */*.o tests *.gcno *.gcda *.info *.gcov  report  *.o Test/*.o Test/*.gcno html_smart_calc.a smart_calc.a CalculatorQT/.qmake.stash build dist

