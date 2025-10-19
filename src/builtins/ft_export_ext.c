/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:13:49 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 11:33:20 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	update_env_var(char **envp, char *key, char *var);
static int	add_env_var(char *var, char **envp);
static int	append_env_var(char **envp, char *key, char *value);
static char	*extract_key(char *var, char *equal, int *is_append);

/**
 * @brief Add or update an environment variable.
 * Provides helpers for the `export` builtin to insert or overwrite entries
 * in the environment using the format "KEY=VALUE".
 * If the input string does not contain '=', no changes are performed.
 *
 * @param var String in the format "KEY=VALUE". If no '=' is present,
 * 	nothing is changed.
 * @param envp Null-terminated array of environment
 * 	strings ("KEY=VALUE") to update.
 * @return 0 on success, 1 on failure (e.g., allocation error).
 */

int	add_or_update_env(char *var, char **envp)
{
	char	*equal;
	char	*key;
	int		status;
	int		is_append;

	equal = ft_strchr(var, '=');
	if (!equal)
		return (0);
	key = extract_key(var, equal, &is_append);
	if (!key)
		return (1);
	if (is_append)
		status = append_env_var(envp, key, equal + 1);
	else if (update_env_var(envp, key, var))
		status = 0;
	else
		status = add_env_var(var, envp);
	free(key);
	return (status);
}

static char	*extract_key(char *var, char *equal, int *is_append)
{
	*is_append = 0;
	if (equal > var && *(equal - 1) == '+')
	{
		*is_append = 1;
		if (equal - var - 1 <= 0)
			return (NULL);
		return (ft_substr(var, 0, equal - var - 1));
	}
	return (ft_substr(var, 0, equal - var));
}

static int	update_env_var(char **envp, char *key, char *var)
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
			envp[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_env_var(char *var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(var);
	envp[i + 1] = NULL;
	return (0);
}

static int	append_env_var(char **envp, char *key, char *value)
{
	int		i;
	int		len;
	char	*old_value;
	char	*new_value;
	char	*key_eq;
	char	*result;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			old_value = ft_strchr(envp[i], '=') + 1;
			new_value = ft_strjoin(old_value, value);
			key_eq = ft_strjoin(key, "=");
			result = ft_strjoin(key_eq, new_value);
			free(envp[i]);
			envp[i] = result;
			free(new_value);
			free(key_eq);
			return (0);
		}
		i++;
	}
	key_eq = ft_strjoin(key, "=");
	envp[i] = ft_strjoin(key_eq, value);
	envp[i + 1] = NULL;
	free(key_eq);
	return (0);
}
