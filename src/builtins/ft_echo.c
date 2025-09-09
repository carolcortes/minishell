/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:18 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/03 22:14:44 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Print arguments to standard output.
 *
 * Implements the behaviour of the `echo` builtin command.
 * Prints all arguments separated by a single space. If the first
 * argument is "-n", the trailing newline is suppressed. Works with
 * a token array of structs (t_token*) passed by address (t_token**).
 *
 * @param args Address of the token array (command + arguments).
 *             (*args)[0].value is "echo"; (*args)[1..].value are args.
 * @return Always returns 0 (success).
 */

int	ft_echo(t_token **args)
{
	int		i;
	int		newline;
	t_token	*av;

	if (!args || !*args)
		return (1);
	av = *args;
	i = 1;
	newline = 1;
	if (av[i].value && strcmp(av[i].value, "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (av[i].value)
	{
		printf("%s", av[i].value);
		if (av[i + 1].value)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
