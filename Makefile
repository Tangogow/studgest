##
## Filename     : Makefile for StudGest project
## Made by      : Alexis Pleney, Razvan Stan
## Started on   : 10/12/19 13:35:46
## Description  : Makefile
##

NAME    = 	studGest

CC			= 	gcc -w

RM			= 	rm -f

SRC    	= 	src/*.c

OBJ			= 	$(SRC:.c=.o)

INC			=		-I inc

LDFLAGS	=		-L lib -l cjson -lm

#CFLAGS 	=		`pkg-config --cflags --libs gtk+-3.0`

DEBUG 	=		-g -Wall -Werror -Wextra -Wdouble-promotion -Wpointer-arith

all:	$(NAME)

$(NAME):
	$(CC) -o $(NAME) $(SRC) $(INC) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(NAME) $(SRC)/*.o

re:		clean all

debug:
	$(CC) -g -o $(NAME) $(SRC) $(INC) $(CFLAGS) $(LDFLAGS) $(DEBUG)
	@echo "**SG: debug-mode**"
