/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:58:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/07 22:29:18 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Exit the minishell.
 *
 * Prints "exit", clears readline history, and terminates the program.
 *
 * @param args Unused command arguments.
 * @return This function does not return.
 */

#include <limits.h>

/* Helper: validate numeric argument and store in *out */
static int	is_valid_numeric(const char *s, long *out)
{
	int			sign;
	unsigned long acc;
	size_t		i;

	if (!s || !*s)
		return (0);
	i = 0;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
		if (!s[i])
			return (0);
	}
	acc = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		acc = acc * 10 + (s[i] - '0');
		if (acc > (unsigned long)LONG_MAX + (sign < 0))
			return (0);
		i++;
	}
	*out = (long)(sign * (long)acc);
	return (1);
}

/*
Exit builtin:
exit                -> exit with 0
exit 42             -> exit 42
exit 256            -> exit 0 (because of unsigned char wrap)
exit 9223372036854775808 -> numeric argument required (overflow) -> exit 255
exit 1 2            -> too many arguments (no exit), return 1
*/

int	ft_exit(t_token **args, char **envp)
{
	long			val;
	unsigned char	code;

	(void)envp;
	// Expect args as NULL-terminated array: args[0]="exit", args[1]=first arg...
	if (!args || !args[0])
		exit(0);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && args[2])
	{
		// Too many arguments IF first argument is numeric; spec keeps shell alive
		if (is_valid_numeric(args[1]->value, &val))
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		// If first arg not numeric we still fall into numeric error path below (exit 255)
	}
	if (args[1])
	{
		if (!is_valid_numeric(args[1]->value, &val))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1]->value, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(255);
		}
		code = (unsigned char)val;
		exit(code);
	}
	// No argument
	exit(0);
}
