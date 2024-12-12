# Variables
NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./ -g -O0

HEADER = libft.h ft_printf.h

SRCS =	ft_printf.c ft_printf_utils.c

BONUS_SRCS = 

# Objetos
OBJ = $(SRCS:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)

EXE = programa

# Regla por defecto: compila el archivo estático y el ejecutable
all: $(NAME)

# Regla para construir el archivo estático
$(NAME): $(OBJ) $(HEADER)
	@ar rcs $(NAME) $(OBJ)

# Regla para construir el ejecutable
$(EXE): $(OBJ) $(NAME)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -L. -lftprintf

# Regla para compilar con las funciones bonus e incluirlas en el archivo estático
bonus: $(OBJ) $(BONUS_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

# Regla para limpiar archivos objeto y el archivo estático
clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

# Regla para limpiar todos los archivos generados por la compilación
fclean: clean
	@rm -f $(NAME)

# Regla para ejecutar el programa
run: $(EXE)
	@./$(EXE)

re: fclean all

# Regla para construir el archivo objeto
%.o: %.c Makefile libft.h ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# Phony targets
.PHONY: all clean fclean re bonus
