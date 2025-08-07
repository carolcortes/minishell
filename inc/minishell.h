/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/06 23:25:52 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

// ANSI Color codes for terminal output formatting:
# define Y		"\033[1;33m"	// Yellow
# define G		"\033[1;32m"	// Green
# define C 		"\033[1;36m"	// Cyan
# define RED	"\033[1;31m"	// Red
# define RST 	"\033[0m"		// Reset to default color

//# define p(...)	printf(__VA_ARGS__)
void	ft_getcwd(char *buf, size_t size);
void	printbanner(void);

#endif
