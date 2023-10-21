CC = clang

SRCPATH := ./src/
INCPATH := ./inc/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard *.c)

CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -O0 -g3 -I$(INCPATH)

OBJS = $(OUTPATH)main.o $(OUTPATH)useful_funcs.o $(OUTPATH)timer.o $(OUTPATH)stack_list.o $(OUTPATH)stack_array.o $(OUTPATH)sequence_check.o $(OUTPATH)my_menu.o

app.exe : $(OBJS)
	$(CC) $^ -o $@ -lm

$(OUTPATH)%.o : */%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : */%.c
	$(CC) $(CFLAGS) -MM $< > $@

include $(SRCS:.c=.d)


.PHONY:
run : app.exe
	./app.exe

.PHONY:
clean : 
	rm -f *.exe *.d *.o out/*.o out/*.gcda out/*.gcno
