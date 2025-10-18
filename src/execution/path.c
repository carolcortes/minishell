/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:43:07 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 16:20:57 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/*static char	*check_absolute_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}*/

static char	*check_path_directory(char *dir, char *command)
{
	char	*full_path;
	char	*temp_path;

	temp_path = ft_strjoin(dir, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin_free(temp_path, command, 1);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char **paths, char *command)
{
	int		i;
	char	*result;

	i = 0;
	while (paths[i])
	{
		result = check_path_directory(paths[i], command);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}

/*char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	result = check_absolute_path(command);
	if (result)
		return (result);
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, command);
	free_array(paths);
	return (result);
}*/
/*static char	*check_explicit_path(char *command)
{
	if (access(command, F_OK) != 0)
	{
		perror("minishell");
		return (NULL);
	}
	if (access(command, X_OK) != 0)
	{
		perror("minishell");
		return (NULL);
	}
	return (ft_strdup(command));
}

char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	// 🚩 Se tiver '/' → é caminho explícito, não procurar em PATH
	if (ft_strchr(command, '/'))
		return (check_explicit_path(command));

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, command);
	free_array(paths);
	return (result);
}*/

// arquivo não existe
// marcador especial
static char	*check_explicit_path(char *command)
{
	if (access(command, F_OK) != 0)
		return (NULL);
	if (access(command, X_OK) != 0)
		return (ft_strdup("PERMISSION_DENIED"));
	return (ft_strdup(command));
}

// 🚩 Se o comando contém '/', trata como caminho explícito
char	*find_command_path(char *command, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (ft_strchr(command, '/'))
		return (check_explicit_path(command));
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, command);
	free_array(paths);
	return (result);
}
