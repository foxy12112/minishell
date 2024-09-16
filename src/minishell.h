/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgmelin <tgmelin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:52:26 by tgmelin           #+#    #+#             */
/*   Updated: 2024/09/16 20:51:35 by tgmelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h> //bool
# include <unistd.h>
# include <stdlib.h>
# include "../include/libft/libft.h"

// GLOBAL_CONFIGURATION		___________________________________________________
# define MAX_PATH_LEN 256
//All allocated memory goes here. a pointer to this structure
//(which is a singleton)
//will be passed to ft_error so it will call the dealloc 
//function with it on error. 
//This structure should contain all information need to propperly unregister and
//deallocate everything.

typedef struct s_allocated_memory
{
	void	*dummy;
}	t_allocated_memory;

//struct that will be handed ot ft error once for setup
typedef struct s_ft_err_data
{
	void	*alloc_data;
	void	(*teardown_func)(void *);
}	t_ft_err_data;

typedef struct s_glob_state
{
	t_allocated_memory	mem;
	bool				is_interactive;
	char				cwd[MAX_PATH_LEN];	
}	t_global_state;

// Utils					___________________________________________________
void	ft_error(t_ft_err_data *_alloc_data,
			const char *_msg, int _exit_status);

// Setup & Teardown			___________________________________________________
void	teardown(void *_alloc_data);
bool	setup(t_global_state *_state);

// Input reading			___________________________________________________
//display prompt and get next command as single c-string
// Our example: ☯ echo $var && echo "Hello, World 'x'" | grep "Hello" > file.txt

bool	get_next_command(char *_out);

// Lexical analysis			___________________________________________________
/*
splits given string into smallest possible token. basicially splits into words 
while respecting " and '
our example becomes:
	1. Command: 	echo
	2. Argument:	*.txt
	3. Operator:	&&
	4. Command: 	echo
	5. Argument: 	"Hello, World '!'"
	6. Pipe:		|
	7. Command:		grep
	8. Argument:	"Hello"
	9. Redirection:	>
	10. Argument:	file.txt
*/

// Syntax Parsing			___________________________________________________
//traverse a token tree for syntax check
//our example is correct so start masturbating

// Expansion				___________________________________________________
/*
replace all variables with their corresponding values
we assume $var is a set variable that hold the string "da var"
our example becomes:
	1. Command: 	echo
	2. Argument:	da var
	3. Operator:	&&
	4. Command: 	echo
	5. Argument: 	"Hello, World '!'"
	6. Pipe:		|
	7. Command:		grep
	8. Argument:	"Hello"
	9. Redirection:	>
	10. Argument:	file.txt
*/

// Word Splitting			___________________________________________________
/*
splits arguments into words
our example becomes:
	1. Command: 	echo
	2. Argument:	da
	3. Argument:	var
	4. Operator:	&&
	5. Command: 	echo
	6. Argument: 	"Hello, World '!'"
	7. Pipe:		|
	8. Command:		grep
	9. Argument:	"Hello"
	10. Redirection:	>
	11. Argument:	file.txt
*/

// Quote removal			___________________________________________________
/*
our example becomes:
	1. Command: 	echo
	2. Argument:	da
	3. Argument:	var
	4. Operator:	&&
	5. Command: 	echo
	6. Argument: 	Hello, World '!'
	7. Pipe:		|
	8. Command:		grep
	9. Argument:	"Hello"
	10. Redirection:	>
	11. Argument:	file.txt
*/

// Redireciton and Piping	___________________________________________________

// Execution				___________________________________________________

#endif