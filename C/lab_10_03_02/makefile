CC := gcc

SRCPATH := ./
INCPATH := ./
UNITPATH := ./

OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))


CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
CHECKFLAGS := -lcheck
BUILDFLAGS := -lm

OBJS := $(OUTPATH)associative_array_impl_2.o
CHECK_OBJS := $(OUTPATH)check_insert.o $(OUTPATH)check_find.o $(OUTPATH)check_remove.o
CHECK_OBJS += $(OUTPATH)check_clear.o $(OUTPATH)check_each.o $(OUTPATH)check_min.o $(OUTPATH)check_max.o

unit_tests.exe: check_funcs.h $(OUTPATH)check_main.o $(CHECK_OBJS) $(OBJS)
	$(CC) $^ -o $@ $(BUILDFLAGS) $(CHECKFLAGS)


$(OUTPATH)%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.lastbuildstate: 
	make clean
	touch $@

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
	rm -f *.exe *.d *.lastbuildstate *.o out/*.o out/*.gcda out/*.gcno
