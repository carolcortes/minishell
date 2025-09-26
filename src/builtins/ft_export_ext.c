/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:13:49 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/26 16:24:05 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_env_var(char **envp, char *key, char *var)
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

int	add_env_var(char *var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(var);
	envp[i + 1] = NULL;
	return (0);
}

int	add_or_update_env(char *var, char **envp)
{
	char	*equal;
	char	*key;
	int		status;

	equal = ft_strchr(var, '=');
	if (!equal)
		return (0);
	key = ft_substr(var, 0, equal - var);
	if (!key)
		return (1);
	if (update_env_var(envp, key, var))
		status = 0;
	else
		status = add_env_var(var, envp);
	free(key);
	return (status);
}
