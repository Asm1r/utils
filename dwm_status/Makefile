PROJ = dwm_status

CC_PREFIX =
CC = $(CC_PREFIX)clang

LDFLAGS= -lasound -lX11
CFLAGS= -std=c99 -Wall -Wextra -Os

SRC += ./main.c
SRC += ./cpu.c
SRC += ./alsa.c
SRC += ./memory.c
SRC += ./net.c

OBJS = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROJ)

.PHONY: clean
clean: 
	rm  *.o
	rm $(PROJ)
