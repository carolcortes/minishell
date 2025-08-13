/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/13 23:03:44 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>		// Input/output operations
# include <stdlib.h>	// General utilities (malloc, free, exit)
# include <unistd.h>	// POSIX operating system API (fork, exec, etc.)
# include <sys/wait.h>	// Process control (wait, waitpid)
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sysexits.h>

# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

// ANSI Color codes for terminal output formatting:
# define Y		"\033[1;33m"	// Yellow
# define G		"\033[1;32m"	// Green
# define C 		"\033[1;36m"	// Cyan
# define RED	"\033[1;31m"	// Red
# define RST 	"\033[0m"		// Reset to default color

# define DELIMITER "\t\n\v\f\r "

typedef struct s_builtin
{
    const char *builtin_name;	// Nome do comando (ex: "echo")
	int (*foo)(char **av);	// Ponteiro para função que implementa o comando
} t_builtin;

//# define p(...)	printf(__VA_ARGS__)
void	ft_getcwd(char *buf, size_t size); // Get current directory
void	printbanner(void); // Shell banner display

/* built-in commands */
int	shell_exit(char **args); /* Shell exit command */

/* sinals.c */
void	setup_signals(void);

#endif
