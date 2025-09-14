/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:43:07 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/14 14:11:08 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
