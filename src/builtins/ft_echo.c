/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:18 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/14 14:33:25 by cgross-s         ###   ########.fr       */
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

	if (!args || !*args)
		return (1);
	i = 1;
	newline = 1;
	//if (args[1] && strcmp(args[1]->value, "-n") == 0)
	if (args[1] && ft_strcmp(args[1]->value, "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]->value);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
