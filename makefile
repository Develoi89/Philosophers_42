NAME = philo

INCLUDE_DIR	= include
SRC_DIR		= src
OBJS_DIR	= objs

SRC =	atoi.c \
		utils.c \
		circle.c \
		errors.c \
		philosophers.c \

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJS = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

RM = rm -rf

HEADER = include/philosophers.h

objs/%.o:src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $<
	@echo "Compiling $^"

all: $(NAME)

$(NAME):$(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./philo 200 800 200 200

PHONY: all clean fclean re
