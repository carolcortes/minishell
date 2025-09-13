/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 16:59:04 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Mude o retorno para int:
int execute_external(t_token **args, char **envp)
{
    pid_t pid;
    int status;
    char *path;
    char **argv;

    argv = tokens_to_argv(args);
    path = find_command_path(argv[0], envp);
    
    if (!path)
    {
        printf("minishell: %s: command not found\n", argv[0]);
        free_argv(argv);
        return (127); // ✅ Retorna código de erro
    }

    pid = fork();
    if (pid == 0)
    {
        execve(path, argv, envp);
        perror("minishell: execve");
        exit(126); // Erro de execução
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
    {
        perror("minishell: fork");
        free(path);
        free_argv(argv);
        return (1);
    }

    free(path);
    free_argv(argv);
    return (WEXITSTATUS(status)); // ✅ Retorna status de saída
}
