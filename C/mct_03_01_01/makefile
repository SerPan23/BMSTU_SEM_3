CC := gcc
SRC := $(wildcard *.c)

OBJS := array.o

app.exe : $(OUTPATH)main.o $(OBJS)
	$(CC) $^ -o $@ -lm

$(OUTPATH)%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : %.c
	$(CC) $(CFLAGS) -MM $< > $@

include $(SRCS:.c=.d)

.PHONY: clean

clean:
	rm -f *.exe *.o