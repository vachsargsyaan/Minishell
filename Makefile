NAME	= minishell

SRC_DIR = src

SRC 	= $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/builtins/*.c)

OBJ_DIR	= obj
OBJ 	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC		= cc
PREFIX		= $(shell pwd)/vacread
HEADER	= $(wildcard includes/*.h) $(wildcard Libft/libft.h)
INCLUDE	= -Iincludes
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
MK		= mkdir -p
LFLAGS  =	-lreadline -L./vacread/lib -lft -L./Libft
IFLAGS  =	-I./vacread/include -ILibft

all: libft $(OBJ_DIR) $(NAME) libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(IFLAGS) -c $< -o $@ 

$(OBJ_DIR)/builtins:
	@$(MK) $@

$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ_DIR)/builtins $(OBJ) $(HEADER)
	$(CC) $(CFLAGS)  $(INCLUDE) $(LFLAGS) $(IFLAGS) -o $(NAME) $(OBJ)

libft:
	make -C Libft

clean:
	@rm -rf $(OBJ)
	make clean -C Libft
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)
	make fclean -C Libft

re: fclean all

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

.PHONY: all clean fclean re readline libft