/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/25 21:59:46 by cgross-s         ###   ########.fr       */
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

//int	ft_env(t_token **args, char **envp)
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
 * freed using free_env().
 *
 * @param envp Null-terminated array of environment strings.
 * @return Pointer to a newly allocated copy of envp,
 *         or NULL on allocation failure.
 */

char	**dup_env(char **envp)
{
	int		i;
	int		count;
	char	**new_env;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

/**
 * @brief Free a duplicated environment array.
 *
 * Iterates through the given environment array and frees
 * each string, then frees the array itself.
 *
 * @param env Null-terminated array of environment strings
 *            previously allocated by dup_env().
 */

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
