NAME			=	libft.a
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
AR				=	ar rcs
SRCS			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
					ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
					ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
					ft_split.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_itoa.c ft_strmapi.c\
					ft_striteri.c ft_putchar_fd.c  ft_putstr_fd.c  ft_putendl_fd.c ft_putnbr_fd.c

BONUS_SRCS		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
					ft_lstmap.c
OBJS			=	$(patsubst %.c, %.o, $(SRCS)) # generating .o filenames from src files`.c ex` ft_atoi.c -> ft_atoi.o
BONUS_OBJS		=	$(patsubst %.c, %.o, $(BONUS_SRCS)) # same for bonus filenames
.DEFAULT_GOAL	=	all

%.o:	%.c # compiles src files`.c and generate .o files ex` ft_atoi.c -> ft_atoi.o
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS) # add only newer objects to the archive
	$(AR)	$(NAME) $?

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

bonus:	$(BONUS_OBJS)
	$(AR)	$(NAME) $?

.PHONY:	all clean fclean re bonus
