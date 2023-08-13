NAME	= minishell

SRC_DIR = src
SRC 	= $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR	= obj
OBJ 	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC		= cc
HEADER	= $(wildcard includes/*.h)
INCLUDE	= -Iincludes
CFLAGS	= -Wall -Wextra -Werror
MK		= mkdir -p
LFLAGS  =	-lreadline -L./vacread/lib
IFLAGS  =	-I./vacread/include

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(IFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS)  $(INCLUDE) $(LFLAGS) $(IFLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all

readline:
	mkdir -p vacread
	cd readline-8.1 && make clean && ./configure --prefix=$(shell find ${HOME} -name vacread 2>/dev/null) && make && make install

.PHONY: all clean fclean re readline