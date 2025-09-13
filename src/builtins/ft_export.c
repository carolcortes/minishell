/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:12 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/13 16:55:30 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Add or update an environment variable.
 *
 * Implements the behaviour of the `export` builtin command.
 * If called without arguments, prints an error message.
 * Otherwise, attempts to add or modify an environment variable
 * using the format "KEY=VALUE".
 *
 * @param args Array of tokens (command + variable assignment).
 *             args[0] is "export", args[1] should be "KEY=VALUE".
 * @return 0 on success, 1 on failure.
 */

int	ft_export(t_token **args)
{
	if (!args[1])
	{
		printf("export: precisa de argumento\n");
		return (1);
	}
	if (putenv(args[1]->value) != 0)
	{
		perror("export");
		return (1);
	}
	return (0);
}
