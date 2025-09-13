/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 18:57:19 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../inc/minishell.h"

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
}*/

#include "../../inc/minishell.h"

int execute_external(t_token **args, char **envp)
{
    pid_t pid;
    int status;
    char *path;
    char **argv;

    // Converter t_token** para char** para execve
    argv = tokens_to_argv(args);
    if (!argv)
        return (1);
    
    // Encontrar o caminho completo do executável
    path = find_command_path(argv[0], envp);
    
    if (!path)
    {
        printf("minishell: %s: command not found\n", argv[0]);
        free_argv(argv);
        return (127); // ✅ Comando não encontrado
    }

    pid = fork();
    if (pid == 0) // Processo filho
    {
        execve(path, argv, envp);
        // Se execve retornar, é erro
        printf("minishell: %s: execution failed\n", argv[0]);
        free(path);
        free_argv(argv);
        exit(126); // ✅ Erro de execução
    }
    else if (pid > 0) // Processo pai
    {
        waitpid(pid, &status, 0);
    }
    else // Erro no fork
    {
        perror("minishell: fork");
        free(path);
        free_argv(argv);
        return (1); // ✅ Erro de fork
    }

    free(path);
    free_argv(argv);
    
    // Retornar o status de saída do comando
    if (WIFEXITED(status))
        return (WEXITSTATUS(status)); // ✅ Status normal de saída
    else if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status)); // ✅ Terminado por sinal
    else
        return (1); // ✅ Fallback
}
