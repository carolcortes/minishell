/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/11 21:31:16 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void execute_external(t_token **args, char **envp)
{
    pid_t pid;
    int status;
    char *path;
    char **argv;

    // ✅ PRIMEIRO: Converter tokens para argv
    argv = tokens_to_argv(args);
    
    // ✅ SEGUNDO: Procurar o comando no PATH (apenas para comandos EXTERNOS)
    path = find_command_path(argv[0], envp);
    
    if (!path)
    {
        printf("minishell: %s: command not found\n", argv[0]);
        free_argv(argv);
        return;
    }

    // ✅ Fork e execução
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
} */

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
    {
        waitpid(pid, &status, 0);
    }
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
