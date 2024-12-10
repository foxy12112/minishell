# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 17:52:31 by ldick             #+#    #+#              #
#    Updated: 2024/12/10 01:20:19 by auplisas         ###   ########.fr        #
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
EXTRA_FLAGS	=	-lreadline
INCLUDES	=	-I includes -I main-libs
SUBMODULE	=	main-libs/Makefile


#################################
#				Files			#
#################################

_REDIRECTS		=	redirect_in.c redirect_out.c redirect_out_append.c redirect_in_heredoc.c redirect_in_heredoc_utils.c
REDIRECTS		=	$(addprefix redirects/, $(_REDIRECTS))

_UTILS		=	env_init.c free.c intialize.c variables.c exec.c pipe.c
UTILS		=	$(addprefix utils/, $(_UTILS))

_BUILTINS		=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILTINS		=	$(addprefix builtins/, $(_BUILTINS))

_SRCS		=	main.c tests.c $(BUILTINS) $(UTILS) $(REDIRECTS)
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
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/redirects"
				@mkdir -p bin/utils
				@mkdir -p bin/builtins
				@mkdir -p bin/redirects

bin/%.o:		srcs/%.c | bin
				@echo "$(GREEN) Compiling $(COMPILER) $(CLR_RMV) -c -o $(YELLOW) $@ $(CYAN) $^ $(GREEN) $(CFLAGS) $(GREEN) $(INCLUDES)"
				@$(COMPILER) -c -o $@ $^ $(CFLAGS) $(INCLUDES)

$(LIBRARY):		$(SUBMODULE)
				@make -C main-libs --silent

$(SUBMODULE):
				git submodule update --init --recursive

$(NAME):		$(LIBRARY) $(OBJS)
				@$(COMPILER) $(EXTRA_FLAGS) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_FLAGS)

clean:
				@cd main-libs && make fclean
				@rm -rf bin

fclean:			clean 
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re