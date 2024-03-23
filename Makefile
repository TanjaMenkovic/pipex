SRC_FILES = pipex_error.c pipex_env.c split_utils.c pipex_file.c pipex_input.c \
			pipex_command.c pipex_process.c ft_split_new.c pipex_main.c 
SRC_BONUS = pipex_error.c pipex_env.c split_utils.c pipex_file.c pipex_input.c \
			pipex_command.c pipex_process.c ft_split_new.c \
			pipex_main_bonus.c
HDR_BONUS = pipex_bonus.h
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = pipex
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(OBJ_BONUS)
			$(CC) $(OBJ_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft/

$(NAME): $(OBJ_FILES)
	${CC} ${CFLAGS} ${OBJ_FILES} ${LIBFT} -o ${NAME} -lft -Llibft

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make clean -C ./libft
	rm -f $(OBJ_FILES)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all bonus clean
