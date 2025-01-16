# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldick <ldick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 12:33:21 by ldick             #+#    #+#              #
#    Updated: 2024/03/20 10:38:31 by ldick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS      = ft_print_char.c				\
            ft_print_hex_lower.c		\
            ft_print_nbr.c				\
            ft_print_pointers.c			\
            ft_print_str.c				\
            ft_print_uns_d.c			\
            ft_print_hex_upper.c		\
            ft_printf.c					\

NAME = libftprintf.a

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = clang

CC_FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c ft_printf.h
		@mkdir -p $(OBJS_DIR)
		@clang $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED)

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all