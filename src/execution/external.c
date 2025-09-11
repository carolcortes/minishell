/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/11 16:20:47 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../inc/minishell.h"

void execute_external(t_token **args, char **envp)
{
    pid_t pid;
    int status;
    char *path;
    char **argv;

    // Converter t_token** para char** para execve
    argv = tokens_to_argv(args);
    
    // Encontrar o caminho completo do executável
    path = find_command_path(argv[0], envp);
    
    if (!path)
    {
        printf("comando não encontrado: %s\n", argv[0]);
        free_argv(argv);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(path, argv, envp);
        perror("execve");
        exit(1);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork");
    }

    free(path);
    free_argv(argv);
}
*/

#include "../../inc/minishell.h"

void execute_external(t_token **args, char **envp)
{
    pid_t pid;
    int status;
    char *path;
    char **argv;

    // Converter t_token** para char** para execve
    argv = tokens_to_argv(args);
    
    // Encontrar o caminho completo do executável
    path = find_command_path(argv[0], envp);
    
    if (!path)
    {
        printf("comando não encontrado: %s\n", argv[0]);
        free_argv(argv);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(path, argv, envp);
        perror("execve");
        exit(1);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork");
    }

    free(path);
    free_argv(argv);
}
