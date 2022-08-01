NAME		= philo

#--------------- DIRS ---------------#

INCLUDE_DIR	= include
SRC_DIR		= src
OBJS_DIR	= objs

#--------------- FILES ---------------#

INC				= -I $(INCLUDE_DIR)

SRC				= philosophers.c \

OBJ				= $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

#--------------- COMPILATION ---------------#

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(INC)

#--------------- RULES ---------------#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "Compiling $^"

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "Built $(NAME)"

clean:
	@rm -rf $(OBJS_DIR)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean