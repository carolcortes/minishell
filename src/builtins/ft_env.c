/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 17:36:24 by cade-oli         ###   ########.fr       */
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

static char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	len;

	if (!key || !envp)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*handle_env_var(const char *str, int *i, char *result,
	t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*value_dup;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name, shell->envp);
	free(var_name);
	if (var_value)
	{
		value_dup = ft_strdup(var_value);
		if (!value_dup)
			return (NULL);
		result = ft_strjoin_free(result, value_dup, 3);
	}
	return (result);
}
