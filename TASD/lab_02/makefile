CC = clang

CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -O0 -g3

OBJS = table.o main.o country.o

app.exe : $(OBJS)
	$(CC) $^ -o $@ -lm

table.o : table.c table.h
	$(CC) $(CFLAGS) $<

country.o : country.c country.h
	$(CC) $(CFLAGS) $<

main.o : main.c
	$(CC) $(CFLAGS) $<


.PHONY:
run : app.exe
	./app.exe

.PHONY:
clean : 
	rm *.o *.exe
