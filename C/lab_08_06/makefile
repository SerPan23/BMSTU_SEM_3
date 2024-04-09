CC := gcc

SRCPATH := ./src/
INCPATH := ./inc/
UNITPATH := ./unit_tests/

OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard *.c)


CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
CHECKFLAGS := -lcheck
BUILDFLAGS := -lm

OBJS := $(OUTPATH)my_matrix.o
CHECK_OBJS := $(OUTPATH)check_mul.o $(OUTPATH)check_pow.o $(OUTPATH)check_new_size_make.o $(OUTPATH)check_square_make.o

app.exe : $(OUTPATH)main.o $(OBJS)
	$(CC) $^ -o $@ $(BUILDFLAGS)

unit_tests.exe: $(OUTPATH)check_main.o $(CHECK_OBJS) $(OBJS)
	$(CC) $^ -o $@ $(BUILDFLAGS) $(CHECKFLAGS)


$(OUTPATH)%.o : */%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : */%.c
	$(CC) $(CFLAGS) -MM $< > $@

%.lastbuildstate: 
	make clean
	touch $@

include $(SRCS:.c=.d)

.PHONY: release
release: CFLAGS += -O3 -g0
release: release.lastbuildstate | app.exe

.PHONY: debug
debug: CFLAGS += $(DEBUGFLAGS) -coverage
debug: BUILDFLAGS += -lgcov -coverage
debug: debug.lastbuildstate | app.exe

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
func: debug 
	cd ./func_tests/scripts/ && ./func_tests.sh
	make coverage


.PHONY:
clean: 
	rm -f *.exe *.d out.txt ./func_tests/scripts/out.txt *.lastbuildstate *.o out/*.o out/*.gcda out/*.gcno
