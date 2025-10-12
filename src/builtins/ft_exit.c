/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:58:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/07 22:45:12 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <limits.h>

/**
 * @brief Exit the minishell.
 *
 * Prints "exit", clears readline history, and terminates the program.
 *
 * @param args Unused command arguments.
 * @return This function does not return.
 */

/* Helper: parse optional sign, update index and sign; return 0 on failure */
static int	parse_sign(const char *s, size_t *i, int *sign)
{
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[(*i)++] == '-')
			*sign = -1;
		if (!s[*i])
			return (0);
	}
	return (1);
}

/* Helper: validate numeric argument and store in *out (<=25 lines) */
static int	is_valid_numeric(const char *s, long *out)
{
	unsigned long	acc;
	int				sign;
	size_t			i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (!parse_sign(s, &i, &sign))
		return (0);
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

/* Helper: print numeric error and exit with 255 */
static void	numeric_error(const char *s)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd((char *)s, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}

int	ft_exit(t_token **args, char **envp)
{
	long			val;
	unsigned char	code;

	(void)envp;
	if (!args || !args[0])
		exit(0);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && args[2] && is_valid_numeric(args[1]->value, &val))
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (args[1])
	{
		if (!is_valid_numeric(args[1]->value, &val))
			numeric_error(args[1]->value);
		code = (unsigned char)val;
		exit(code);
	}
	exit(0);
}
