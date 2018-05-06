PROJ = dwm_status

CC_PREFIX =
CC = $(CC_PREFIX)clang

LDFLAGS= -lasound -lX11
CFLAGS= -std=c99 -Wall -Wextra -Os

SRC_DIR = ./src
INC_DIR = ./inc


SRC += $(SRC_DIR)/main.c
SRC += $(SRC_DIR)/cpu.c
SRC += $(SRC_DIR)/alsa.c
SRC += $(SRC_DIR)/memory.c
SRC += $(SRC_DIR)/net.c

UNITY_SRC = ./Unity/src
UNITY_INC = ./Unity/src
TEST_SRC_DIR = ./tests
TEST_INC_DIR = $(TEST_SRC_DIR)

TEST_SRC += $(TEST_SRC_DIR)/test_$(PROJ).c
TEST_SRC += $(UNITY_SRC)/unity.c

OBJS = $(SRC:.c=.o)
TEST_OBJS = $(TEST_SRC:.c=.o) 

%.o: %.c
	@$(CC) -I$(SRC_DIR) -I$(INC_DIR) -I$(TEST_INC_DIR) -I$(UNITY_INC) -c $(CFLAGS) $< -o $@

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROJ)

test: $(TEST_OBJS)
	@$(CC) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_SRC_DIR)/test_$(PROJ)
	@$(TEST_SRC_DIR)/test_$(PROJ)

.PHONY: clean
clean: 
	rm $(SRC_DIR)/*.o \
	 $(PROJ) \
	 $(UNITY_SRC)/*.o \
	 $(TEST_SRC_DIR)/*.o
