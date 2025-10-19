/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:22 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 10:59:20 by cade-oli         ###   ########.fr       */
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

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_var(char **envp, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			while (envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return ;
		}
		i++;
	}
}

int	ft_unset(t_token **args, char **envp)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]->value))
		{
			fprintf(stderr, "unset: `%s': not a valid identifier\n",
				args[i]->value);
			exit_status = 1;
		}
		else
			remove_var(envp, args[i]->value);
		i++;
	}
	return (exit_status);
}
