# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 17:52:31 by ldick             #+#    #+#              #
#    Updated: 2024/12/06 06:12:02 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishella

#################################
#				Colors			#
#################################

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
BOLD_BLUE	:= \033[0;34m

#################################
#				Flags			#
#################################

COMPILER	=	cc
LIB_FLAGS	=	main-libs/libs.a
# CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-I includes -I main-libs
SUBMODULE	=	main-libs/Makefile


#################################
#				Files			#
#################################
_UTILS		=	env_init.c free.c intialize.c variables.c exec.c
UTILS		=	$(addprefix utils/, $(_UTILS))

_BUILTINS		=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILTINS		=	$(addprefix builtins/, $(_BUILTINS))

_SRCS		=	main.c tests.c $(BUILTINS) $(UTILS) 
SRCS		=	$(addprefix srcs/, $(_SRCS))

OBJS		=	$(SRCS:srcs/%.c=bin/%.o)
LIBRARY		=	main-libs/libs.a

#################################
#				Rules			#
#################################
all:			$(NAME)

bin:
				@echo "\t\t\t$(BLUE) Making bin directory"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/utils"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/builtins"
				@mkdir -p bin/utils
				@mkdir -p bin/builtins

bin/%.o:		srcs/%.c | bin
				@echo "$(GREEN) Compiling $(COMPILER) $(CLR_RMV) -c -o $(YELLOW) $@ $(CYAN) $^ $(GREEN) $(CFLAGS) $(GREEN) $(INCLUDES)"
				@$(COMPILER) -c -o $@ $^ $(CFLAGS) $(INCLUDES)

$(LIBRARY):		$(SUBMODULE)
				@make -C main-libs --silent

$(SUBMODULE):
				git submodule update --init --recursive

$(NAME):		$(LIBRARY) $(OBJS)
				@$(COMPILER) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_FLAGS)

clean:
				@cd main-libs && make fclean
				@rm -rf bin

fclean:			clean 
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re