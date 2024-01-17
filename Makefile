NAME	= minishell

SRC_DIR = src

SRC 	= $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/build/*.c)

OBJ_DIR	= obj
OBJ 	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC		= cc
HEADER	= $(wildcard includes/*.h) $(wildcard Libft/libft.h)
INCLUDE	= -Iincludes
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
MK		= mkdir -p
LFLAGS  =	-lreadline -L./vacread/lib -lft -L./Libft
IFLAGS  =	-I./vacread/include -ILibft

all: libft $(OBJ_DIR) $(NAME) libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(IFLAGS) -c $< -o $@ 

$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)

$(NAME): $(OBJ) $(HEADER)
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
	mkdir -p vacread
	cd readline-master && make clean && ./configure --prefix=$(shell find ${HOME} -name vacread 2>/dev/null) && make && make install

.PHONY: all clean fclean re readline libft