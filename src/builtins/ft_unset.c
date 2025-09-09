/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:22 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/02 22:50:53 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Remove an environment variable.
 *
 * Implements the behaviour of the `unset` builtin command.
 * Removes the variable specified by the argument from the
 * environment. If no argument is provided, prints an error.
 *
 * @param args Array of tokens (command + variable name).
 *             args[0] is "unset", args[1] is the variable name.
 * @return 0 on success, 1 if no argument is given or
 *         if the variable could not be removed.
 */

int	ft_unset(t_token **args)
{
	if (!args[1])
	{
		printf("unset: precisa de argumento\n");
		return (1);
	}
	if (unsetenv(args[1]->value) != 0)
	{
		perror("unset");
		return (1);
	}
	return (0);
}
