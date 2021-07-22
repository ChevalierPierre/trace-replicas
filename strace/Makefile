##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

.SUFFIXES: .c .o

CC=				gcc

FLAGS=			-g3 -W -Wall -Wextra -I./include

LFLAGS=			-L./lib

NAME=			strace

INCLUDE_DIR=	./include/
INCLUDE=		$(INCLUDE_DIR)/strace.h \
				$(INCLUDE_DIR)/syscalls.h

SRC_DIR=		./src
SRC=			$(SRC_DIR)/main.c \
				$(SRC_DIR)/strace.c \
				$(SRC_DIR)/disp.c

OBJ=			$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

.c.o:
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean:			clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
