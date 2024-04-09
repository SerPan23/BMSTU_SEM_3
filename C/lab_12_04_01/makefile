# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib/
CC := gcc

SRCPATH := ./src/
LIBPATH := ./lib/
INCPATH := ./inc/
UNITPATH := ./unit_tests/

OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard *.c)


# CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH) -I$(LIBPATH)
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH) -I$(LIBPATH)
DEBUGFLAGS := -O0 -g3
CHECKFLAGS := -lcheck
BUILDFLAGS := -lm

CHECKOBJS := $(OUTPATH)check_main.o $(OUTPATH)check_key.o $(OUTPATH)check_mysort.o
STATLIBOBJS := $(LIBPATH)libfilter.a


app.exe: $(OUTPATH)main.o $(STATLIBOBJS)
	$(CC) -o $@ $^ $(BUILDFLAGS)

unit_tests.exe: $(CHECKOBJS) $(STATLIBOBJS)
	$(CC) -o $@ $^ $(BUILDFLAGS) $(CHECKFLAGS)


app_dlyn_1.exe: $(LIBPATH)libfilter.so $(OUTPATH)main.o
	$(CC) -o $@ $(OUTPATH)main.o -L$(LIBPATH) -lfilter $(BUILDFLAGS)

app_dlyn_2.exe: $(LIBPATH)libfilter.so $(OUTPATH)main_2.o
	$(CC) -o $@ $(OUTPATH)main_2.o -ldl $(BUILDFLAGS)



$(LIBPATH)libfilter.a: $(LIBPATH)filter_lib.c
	$(CC) $(CFLAGS) -c $< -o $(OUTPATH)filter_lib.o
	ar cr $@ $(OUTPATH)filter_lib.o
	ranlib $@

$(LIBPATH)libfilter.so: $(LIBPATH)filter_lib.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $(OUTPATH)filter_lib.o
	$(CC) -o $@ -shared $(OUTPATH)filter_lib.o


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

.PHONY: app_dlyn_1
app_dlyn_1: app_dlyn_1.lastbuildstate | app_dlyn_1.exe

.PHONY: app_dlyn_2
app_dlyn_2: app_dlyn_2.lastbuildstate | app_dlyn_2.exe

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
	rm -f *.exe *.d out.txt *.lastbuildstate *.o out/*.o out/*.gcda out/*.gcno
