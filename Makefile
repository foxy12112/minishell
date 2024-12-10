# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldick <ldick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 17:52:31 by ldick             #+#    #+#              #
#    Updated: 2024/12/10 11:24:37 by ldick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

#################################################################################################
#											Colors												#
#################################################################################################

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
BOLD_BLUE	:= \033[0;34m
NC			:= \033[0m

#################################################################################################
#											Flags												#
#################################################################################################

COMPILER	=	cc
INCLUDES	=	-I includes -I main-libs
SUBMODULE	=	main-libs/Makefile
LIB_FLAGS	=	-ls -Lmain-libs
CFLAGS		=	-Wall -Werror -Wextra -g #-fsanitize=address
EXTRA_FLAGS	=	-lreadline
ERROR_FILE	=	error.log

#################################################################################################
#											Sources												#
#################################################################################################

_UTILS		=	env_init.c free.c intialize.c variables.c exec.c parsing.c signal.c
UTILS		=	$(addprefix utils/, $(_UTILS))

_BUILTINS		=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILTINS		=	$(addprefix builtins/, $(_BUILTINS))

_SRCS		=	main.c tests.c $(BUILTINS) $(UTILS) 
SRCS		=	$(addprefix srcs/, $(_SRCS))

OBJS		=	$(SRCS:srcs/%.c=bin/%.o)
LIBRARY		=	main-libs/libs.a

#################################################################################################
#											Rules												#
#################################################################################################

all:			$(NAME)

bin:
				@echo "\t\t\t$(BLUE) Making bin directory"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/utils"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/builtins"
				@mkdir -p bin/utils
				@mkdir -p bin/builtins

bin/%.o:		srcs/%.c | bin
				@echo "$(GREEN) Compiling $(Compiler) $(CLR_RMV) -c -o $(YELLOW) $@ $(CYAN) $^ $(GREEN) $(EXTRA_FLAGS) $(CFLAGS) $(GREEN) $(INCLUDES) $(NC)"
				@$(COMPILER) -c -o $@ $^ $(EXTRA_FLAGS) $(CFLAGS) $(INCLUDES) 2> $(ERROR_FILE) || (cat $(ERROR_FILE) && echo "$(RED)Compilation failed :0\nfailed file: \t\t$(YELLOW)$<$(NC)\n\n" && exit 1)

$(LIBRARY):		$(SUBMODULE)
				@make -C main-libs --silent

$(SUBMODULE):
				@git submodule update --init --recursive

$(NAME):		$(LIBRARY) $(OBJS)
				@$(COMPILER) $(EXTRA_FLAGS) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_FLAGS)
				@echo "\t\t\t\t$(RED) compilation success :3"

clean:
				@rm -rf bin
				@rm -f $(ERROR_FILE)
				@rm -f output*.log

fclean:			clean
				@make fclean -C main-libs --silent
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re