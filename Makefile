NAME		= pipex
HPATH = 	-Iincludes
CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

SRC_PATH = ./src/

SRC_FILES = pipex.c split.c utils.c finder.c

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))

OBJS		= $(SRC:.c=.o)

RM			= rm -f

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(HPATH) $(SRC) -o $(NAME)

all: 		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean all