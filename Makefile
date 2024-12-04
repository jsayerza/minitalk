SRCS	= client.c #server.c
OBJ	:= $(SRCS:%.c=%.o)
NAME	= minitalk
CC	= cc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
EXE	= client
PARAMS	= 123 missatxa

all:	$(NAME)

%.o:	%.c
	$(CC) $(FLAGS) -Ilibft -Iftpf -c $? -o $@

$(NAME):server client

server:	server.o
	@make -C libft
	@make -C ftpf
	$(CC) $(CFLAGS) $? -Llibft -lft -Lftpf -lftprintf -o server
	
client:	client.o
	@make -C libft
	@make -C ftpf
	$(CC) $(CFLAGS) $? -Llibft -lft -Lftpf -lftprintf -o client
	
libft:	
	make -C libft
	
ftpf:	
	make -C ftpf

clean:
	make clean -C libft
	make clean -C ftpf
	$(RM) $(OBJ)

fclean:	clean
	$(RM) server client

re:	fclean all

run:
	@if [ -f "$(EXE)" ]; then \
		clear; \
		#echo "$(EXE) trobat!"; \
		./$(EXE) $(PARAMS); \
	else \
		echo "$(EXE) no trobat. Run 'make' abans"; \
	fi


.PHONY:	libft ftpf

