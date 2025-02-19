# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 17:52:31 by ldick             #+#    #+#              #
#    Updated: 2025/01/17 22:45:39 by macbook          ###   ########.fr        #
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
LIB_FLAGS	=	-lreadline -ls -Lmain-libs
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address
EXTRA_FLAGS	=	
ERROR_FILE	=	error.log

#################################################################################################
#											Sources												#
#################################################################################################

_EXECUTION		=	execute_builtins.c execute_command.c execute_redirects.c execute_pipes.c exec.c
EXECUTION		=	$(addprefix execution/, $(_EXECUTION))

_PARSING		=	parse_errors.c expander.c redirect_parse.c redirect_parse_utils.c cmd_parse.c pipe_split.c quotes_utils.c
PARSING			=	$(addprefix parsing/, $(_PARSING))

_REDIRECTS		=	heredoc_utils.c redirect_in.c redirect_out.c redirect_out_append.c redirect_in_heredoc.c redirect_to_terminal.c
REDIRECTS		=	$(addprefix redirects/, $(_REDIRECTS))

_UTILS			=	free_linked_lists.c print_test_files.c history.c ft_split_delimiters.c ft_split_delimiters_utils.c unclosed_quotes.c env_init.c free.c utils.c intialize.c variables.c loop_utils.c ft_split_byfirstequal.c ft_split_whitespaces.c ft_split_quotes.c signal.c
UTILS			=	$(addprefix utils/, $(_UTILS))

_BUILTINS		=	cd.c echo.c env.c exit.c export.c export_utils.c pwd.c unset.c
BUILTINS		=	$(addprefix builtins/, $(_BUILTINS))

_SRCS			=	main.c $(BUILTINS) $(UTILS) $(REDIRECTS) $(PARSING) $(EXECUTION)
SRCS			=	$(addprefix srcs/, $(_SRCS))

OBJS			=	$(SRCS:srcs/%.c=bin/%.o)
LIBRARY			=	main-libs/libs.a

#################################################################################################
#											Rules												#
#################################################################################################

all:			$(NAME)

bin:
				@echo "\t\t\t$(BLUE) Making bin directory"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/utils"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/builtins"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/redirects"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/parsing"
				@echo "\t\t\t$(BOLD_BLUE) mkdir -p bin/execution"
				@mkdir -p bin/utils
				@mkdir -p bin/builtins
				@mkdir -p bin/redirects
				@mkdir -p bin/parsing
				@mkdir -p bin/execution

bin/%.o:		srcs/%.c | bin
				@echo "$(GREEN) Compiling $(Compiler) $(CLR_RMV) -c -o $(YELLOW) $@ $(CYAN) $^ $(GREEN) $(EXTRA_FLAGS) $(CFLAGS) $(GREEN) $(INCLUDES) $(NC)"
				@$(COMPILER) -c -o $@ $^ $(EXTRA_FLAGS) $(CFLAGS) $(INCLUDES) 2> $(ERROR_FILE) || (cat $(ERROR_FILE) && echo "$(RED)Compilation failed :0\nfailed file: \t\t$(YELLOW)$<$(NC)\n\n" && exit 1$(NC))

$(LIBRARY):		$(SUBMODULE)
				@make -C main-libs --silent

$(SUBMODULE):
				@git submodule update --init --recursive

$(NAME): $(LIBRARY) $(OBJS)
				@$(COMPILER) -o $(NAME) $(OBJS) $(LIB_FLAGS) $(EXTRA_FLAGS) $(CFLAGS)
				@echo "\t\t\t\t$(RED) compilation success :3$(NC)"
				@mkdir -p .git/permanent_history

clean:
				@rm -rf bin
				@rm -f $(ERROR_FILE)
				@rm -f output*.log

fclean:			clean
				@make fclean -C main-libs --silent
				@rm -f $(NAME)

history:		clean
				@rm -rf .git/permanent_history

re:				fclean all

.PHONY:			all clean fclean re