/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:43:07 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 19:00:05 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Em src/execution/path.c
/*#include "../../inc/minishell.h"

char *find_command_path(char *command, char **envp)
{
    char *path;
    char *path_env;
    char **paths;
    int i;
    
    // Se o comando já tem caminho absoluto ou relativo
    if (access(command, X_OK) == 0)
        return (ft_strdup(command));
    
    // Buscar PATH no environment
    path_env = NULL;
    i = 0;
    while (envp[i] && !path_env)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            path_env = envp[i] + 5;
        i++;
    }
    
    if (!path_env)
        return (NULL);
    
    // Dividir PATH por ':'
    paths = ft_split(path_env, ':');
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        path = ft_strjoin_free(path, command, 1);
        
        if (access(path, X_OK) == 0)
        {
            free_array(paths);
            return (path);
        }
        
        free(path);
        i++;
    }
    
    free_array(paths);
    return (NULL);
}*/

#include "../../inc/minishell.h"

char *find_command_path(char *command, char **envp)
{
    char *path;
    char *path_env;
    char **paths;
    int i;
    
    // Se já é um caminho absoluto/relativo
    if (access(command, X_OK) == 0)
        return (ft_strdup(command));
    
    // Buscar variável PATH
    path_env = NULL;
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }
    
    if (!path_env)
        return (NULL);
    
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        path = ft_strjoin_free(path, command, 1);
        
        if (access(path, X_OK) == 0)
        {
            free_array(paths);
            return (path);
        }
        
        free(path);
        i++;
    }
    
    free_array(paths);
    return (NULL);
}
