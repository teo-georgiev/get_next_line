# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgeorgie <tgeorgie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 10:15:14 by tgeorgie          #+#    #+#              #
#    Updated: 2023/11/16 15:01:00 by tgeorgie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	gnl.out
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

DEBUG_NAME	=	debug.out
DEBUG_FLAGS	=	-g -fsanitize=address,undefined,integer

GNL_FN		=	get_next_line get_next_line_utils main
GNL_C		=	$(addsuffix .c, $(GNL_FN))

$(NAME):
	$(CC) $(CFLAGS) $(GNL_C) -o $@

$(DEBUG_OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(DEBUG_OBJ_DIR)$(subst $(SRC_DIR),,$(dir $<))
	@echo Building debug $<
	@$(CC) $(DEBUG_FLAGS) -c $< -o $@

$(DEBUG_NAME): $(DEBUG_OBJS)
	@echo Compiling debug executable
	@$(CC) $(DEBUG_FLAGS) $(DEBUG_OBJS) -o $@
	@echo Debug done

debug: debug.out

all: $(NAME)

clean:
	rm -f $(PRINT_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re bonus
