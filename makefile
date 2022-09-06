NAME = philosophers

SRCS =	src/atoi.c \
		src/utils.c\
		src/circle.c\
		src/errors.c \
		src/philosophers.c \

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)

RM = rm -rf

HEADER = include/philosophers.h

all: $(NAME)

$(NAME):$(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./philosophers 10 42 42 42

PHONY: all clean fclean re
