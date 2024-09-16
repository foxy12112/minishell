# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgmelin <tgmelin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:43:31 by tgmelin           #+#    #+#              #
#    Updated: 2024/09/16 20:06:59 by tgmelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = maxishell

#################################
#			Config				#
#################################

CC = cc

#################################
#			Files				#
#################################

SRC 		= src/main.c src/setup.c src/teardown.c src/Utils/ft_error.c
OBJ 		= $(SRC:.c=.o)
BUILD_DIR	= build
LIBFT_DIR	= include/libft
LIBS		= include/libft.a

#################################
#			Flags				#
#################################

EXTRA_FLAGS		= -pthread
REQUIRED_FLAGS	= $(EXTRA_FLAGS) -Wall -Wextra -Werror 
DEBUG_FLAGS		= $(REQUIRED_FLAGS) -g -fsanitize=address -fsanitize=undefined -O0
DEV_FLAGS		= $(REQUIRED_FLAGS) -g -march=native -O0
RELEASE_FLAGS	= $(REQUIRED_FLAGS) -fstack-protector -flto -fomit-frame-pointer -O3 -fvisibility=hidden 
EVAL_FLAGS		= $(RELEASE_FLAGS) -march=native

#################################
#			Internals			#
#################################

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
BOLD_BLUE	:= \033[0;34m


#################################
#			Rules				#
#################################

all: $(NAME)

mkdirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/Release
	mkdir -p $(BUILD_DIR)/Dev
	mkdir -p $(BUILD_DIR)/Debug
	mkdir -p $(BUILD_DIR)/Eval

deps: mkdirs
	git submodule update --init --recursive
	make -C $(LIBFT_DIR) --silent

depsclean:
	make -C $(LIBFT_DIR) clean

depsfclean:
	make -C $(LIBFT_DIR) fclean

$(NAME): release

release: $(OBJ) deps
	$(CC) -o $(BUILD_DIR)/Release/$(NAME) $(OBJ) $(RELEASE_FLAGS) $(LIBS)

dev: $(OBJ) deps
	$(CC) -o $(BUILD_DIR)/Dev/$(NAME) $(OBJ) $(DEV_FLAGS) $(LIBS)

debug: $(OBJ) deps
	$(CC) -o $(BUILD_DIR)/Debug/$(NAME) $(OBJ) $(DEBUG_FLAGS) $(LIBS)

eval: $(OBJ) deps
	$(CC) -o $(BUILD_DIR)/Eval/$(NAME) $(OBJ) $(EVAL_FLAGS) $(LIBS)

clean: depsclean
	rm -f $(OBJ)

fclean: clean depsfclean
	rm -f $(BUILD_DIR)/Release/$(NAME)
	rm -f $(BUILD_DIR)/Dev/$(NAME)
	rm -f $(BUILD_DIR)/Debug/$(NAME)
	rm -f $(BUILD_DIR)/Eval/$(NAME)

re: fclean all

.PHONY: $(NAME) mkdirs deps depsclean depsfclean all release dev debug eval clean fclean re
