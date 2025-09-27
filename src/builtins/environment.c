/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:08:10 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/27 18:06:15 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int	add_variable_to_env(char *var, char ***envp)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc((count + 2) * sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (1);
		}
		i++;
	}
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	free_env(*envp);
	*envp = new_env;
	return (0);
}*/

static char	**alloc_new_env(int count)
{
	char	**new_env;

	new_env = malloc((count + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static int	copy_old_env(char **new_env, char **old_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_variable_to_env(char *var, char ***envp)
{
	int		count;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = alloc_new_env(count);
	if (!new_env)
		return (1);
	if (copy_old_env(new_env, *envp, count))
		return (1);
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	free_env(*envp);
	*envp = new_env;
	return (0);
}
