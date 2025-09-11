/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/11 21:23:06 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../inc/minishell.h"

void execute_pipeline(t_command *pipeline, char **envp)
{
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd = pipeline;

    while (cmd)
    {
        if (cmd->next && pipe(pipe_fd) == -1)
        {
            perror("pipe");
            return;
        }

        pid = fork();
        if (pid == 0) // Child process
        {
            // Redirect input
            if (input_fd != STDIN_FILENO)
            {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            // Redirect output
            if (cmd->next)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // Execute command
            if (is_builtin(cmd->args))
                exit(exec_builtin(cmd->args, envp));
            else
                execute_external(cmd->args, envp);
            exit(1);
        }
        else if (pid < 0)
        {
            perror("fork");
            return;
        }

        // Parent process
        if (input_fd != STDIN_FILENO)
            close(input_fd);
        
        if (cmd->next)
        {
            close(pipe_fd[1]);
            input_fd = pipe_fd[0];
        }

        cmd = cmd->next;
    }

    // Wait for all children
    while (wait(NULL) > 0);
}*/

// Em src/execution/execute_pipeline.c
#include "../../inc/minishell.h"

void execute_pipeline(t_command *pipeline, char **envp)
{
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd = pipeline;
    int cmd_count = 0;

    // Contar quantos comandos na pipeline
    while (cmd)
    {
        cmd_count++;
        cmd = cmd->next;
    }
    cmd = pipeline; // Resetar para o início

    // Executar cada comando na pipeline
    while (cmd)
    {
        // Criar pipe para todos os comandos exceto o último
        if (cmd->next && pipe(pipe_fd) == -1)
        {
            perror("minishell: pipe");
            return;
        }

        pid = fork();
        if (pid == 0) // Processo filho
        {
            // Redirecionar entrada (do pipe anterior ou stdin)
            if (input_fd != STDIN_FILENO)
            {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            // Redirecionar saída (para o próximo pipe ou stdout)
            if (cmd->next)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // Executar o comando
            if (is_builtin(cmd->args))
            {
                int exit_status = exec_builtin(cmd->args, envp);
                exit(exit_status);
            }
            else
            {
                execute_external(cmd->args, envp);
                exit(127); // Se execute_external retornar, significa que falhou
            }
        }
        else if (pid < 0) // Erro no fork
        {
            perror("minishell: fork");
            return;
        }

        // Processo pai: fechar file descriptors não mais necessários
        if (input_fd != STDIN_FILENO)
            close(input_fd);
        
        if (cmd->next)
        {
            close(pipe_fd[1]); // Fechar escrita do pipe atual
            input_fd = pipe_fd[0]; // Salvar leitura para próximo comando
        }

        cmd = cmd->next;
    }

    // Esperar todos os processos filhos terminarem
    int status;
    while (wait(&status) > 0)
    {
        // Você pode capturar o status de saída do último comando aqui
        // se quiser implementar $? mais precisamente
    }
}
