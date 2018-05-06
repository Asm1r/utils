PROJ = dwm_status

CC_PREFIX =
CC = $(CC_PREFIX)clang

LDFLAGS= -lasound -lX11
CFLAGS= -std=c99 -Wall -Wextra -Os
SRC_DIR = ./src

SRC += $(SRC_DIR)/main.c
SRC += $(SRC_DIR)/cpu.c
SRC += $(SRC_DIR)/alsa.c
SRC += $(SRC_DIR)/memory.c
SRC += $(SRC_DIR)/net.c

OBJS = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROJ)

.PHONY: clean
clean: 
	rm  $(SRC_DIR)/*.o
	rm $(PROJ)
