SRCS = ft_printf.c ft_printf_utils.c
OBJ = $(SRCS:.c=.o)
NAME = libftprintf.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all:	$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all 

.PHONY: all clean fclean re
