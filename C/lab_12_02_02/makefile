CC := gcc

SRCPATH := ./src/
INCPATH := ./inc/
UNITPATH := ./unit_tests/
LIBPATH := ./lib/

OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard *.c)


CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH) -I$(LIBPATH)
DEBUGFLAGS := -O0 -g3
CHECKFLAGS := -lcheck
BUILDFLAGS := -lm


CHECKOBJS := $(OUTPATH)check_main.o $(OUTPATH)check_fibonacci.o $(OUTPATH)check_copy.o
STATLIBOBJS := $(LIBPATH)libarr.a


unit_tests.exe: $(CHECKOBJS) $(STATLIBOBJS)
	$(CC) -o $@ $^ $(BUILDFLAGS) $(CHECKFLAGS)


$(LIBPATH)libarr.a: $(LIBPATH)array_lib.c
	$(CC) $(CFLAGS) -c $< -o $(OUTPATH)array_lib.o
	ar cr $@ $(OUTPATH)array_lib.o
	ranlib $@

$(LIBPATH)libarr.so: $(LIBPATH)array_lib.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $(OUTPATH)array_lib.o
	$(CC) -o $@ -shared $(OUTPATH)array_lib.o


$(OUTPATH)%.o : $(SRCPATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : $(SRCPATH)%.c
	$(CC) $(CFLAGS) -MM $< > $@

$(OUTPATH)%.o : $(UNITPATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : $(UNITPATH)%.c
	$(CC) $(CFLAGS) -MM $< > $@

%.lastbuildstate: 
	make clean
	touch $@

include $(SRCS:.c=.d)

.PHONY: run
run: run.lastbuildstate | $(LIBPATH)libarr.so
	python3 $(SRCPATH)main.py

.PHONY: unit_test_build
unit_test_build: CFLAGS += $(DEBUGFLAGS) -coverage
unit_test_build: BUILDFLAGS += -lgcov -coverage
unit_test_build: unit.lastbuildstate | unit_tests.exe

.PHONY:
unit: unit_test_build 
	./unit_tests.exe
	make coverage


.PHONY: coverage
coverage:
	cd $(OUTPATH) && gcov ./*.gcno

.PHONY:
clean: 
	rm -f *.exe *.d out.txt *.lastbuildstate *.o out/*.o out/*.gcda out/*.gcno
