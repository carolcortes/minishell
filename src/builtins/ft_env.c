/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 11:30:16 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Print the shell environment variables.
 *
 * Iterates through the given environment array and prints each
 * variable in the format "KEY=VALUE". This function mimics the
 * behaviour of the `env` builtin command.
 *
 * @param args Array of tokens (unused).
 * @param envp Null-terminated array of environment strings.
 * @return Always returns 0 (success).
 */

int	ft_env(t_token **args, char **envp)
{
	int	i;

	(void)args;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Duplicate the environment array.
 *
 * Allocates a new array of strings and duplicates each entry
 * from the provided environment. The returned array must be
 * freed using free_strings().
 *
 * @param envp Null-terminated array of environment strings.
 * @return Pointer to a newly allocated copy of envp,
 *         or NULL on allocation failure.
 */

char	**dup_env(char **envp)
{
	int		i;
	int		count;
	int		capacity;
	char	**new_env;

	count = 0;
	while (envp[count])
		count++;
	capacity = count + (count / 2) + 10;
	new_env = malloc((capacity + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	while (i <= capacity)
		new_env[i++] = NULL;
	return (new_env);
}
