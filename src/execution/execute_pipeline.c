/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/11 16:30:01 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
}
