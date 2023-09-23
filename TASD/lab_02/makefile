CC = clang

CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -O0 -g3

OBJS = table.o main.o country.o menu.o useful_funcs.o

app.exe : $(OBJS)
	$(CC) $^ -o $@ -lm

table.o : table.c table.h defines.h
	$(CC) $(CFLAGS) $<

country.o : country.c country.h defines.h
	$(CC) $(CFLAGS) $<

menu.o : menu.c menu.h defines.h
	$(CC) $(CFLAGS) $<

useful_funcs.o : useful_funcs.c useful_funcs.h defines.h
	$(CC) $(CFLAGS) $<

main.o : main.c
	$(CC) $(CFLAGS) $<


.PHONY:
run : app.exe
	./app.exe

.PHONY:
clean : 
	rm *.o *.exe
