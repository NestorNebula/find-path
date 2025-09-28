CC = cc
CFLAGS = -Wall -Wextra -Werror

EXEC = find_path
GEN = gen_grid

SRC_DIR = src
EXEC_SRC = find_path.c $(SRC_DIR)/grid.c $(SRC_DIR)/queue.c \
	   $(SRC_DIR)/square.c $(SRC_DIR)/resolve.c $(SRC_DIR)/input.c \
	   $(SRC_DIR)/output.c 
GEN_SRC = gen_grid.c $(SRC_DIR)/random.c $(SRC_DIR)/grid.c \
	  $(SRC_DIR)/square.c $(SRC_DIR)/input.c \
	  $(SRC_DIR)/output.c

INCLUDE_DIR = include

EXEC_OBJ = $(EXEC_SRC:.c=.o)
GEN_OBJ = $(GEN_SRC:.c=.o)

all: $(EXEC) $(GEN)

$(SRC_DIR)/grid.o: $(INCLUDE_DIR)/grid.h

$(SRC_DIR)/queue.o: $(INCLUDE_DIR)/queue.h

$(SRC_DIR)/square.o: $(INCLUDE_DIR)/square.h

$(SRC_DIR)/resolve.o: $(INCLUDE_DIR)/resolve.h

$(SRC_DIR)/input.o: $(INCLUDE_DIR)/input.h

$(SRC_DIR)/output.o: $(INCLUDE_DIR)/output.h

$(SRC_DIR)/random.o: $(INCLUDE_DIR)/random.h

find_path.o: $(INCLUDE_DIR)/io.h

gen_grid.o: $(INCLUDE_DIR)/io.h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE_DIR)

$(EXEC): $(EXEC_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

$(GEN): $(GEN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(EXEC_OBJ) $(GEN_OBJ)

fclean: clean
	rm -rf $(EXEC) $(GEN)

re: fclean all
