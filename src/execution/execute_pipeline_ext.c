/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/22 14:38:51 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect_input(int input_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(1);
		}
		close(input_fd);
	}
}

void	redirect_output(int pipe_fd[2])
{
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 stdout");
		exit(1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	execute_command(t_command *cmd, char **envp)
{
	int	exit_status;

	if (is_builtin(cmd->args))
	{
		exit_status = exec_builtin(cmd->args, envp);
		exit(exit_status);
	}
	else
	{
		exit_status = execute_external(cmd->args, envp);
		exit(exit_status);
	}
}

/*void	handle_child_process(t_command *cmd, int input_fd,
    int pipe_fd[2], char **envp)
{
    // 1. Redirecionamentos de PIPE (têm menor prioridade)
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (cmd->next)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }

    // 2. Redirecionamentos de ARQUIVO (sobrescrevem pipes)
    if (!apply_redirections(cmd))
        exit(1);

    // 3. Executar comando
    if (is_builtin(cmd->args))
        exit(exec_builtin(cmd->args, envp));
    else
        exit(execute_external(cmd->args, envp));
}*/

void	handle_child_process(t_command *cmd, int input_fd,
	int pipe_fd[2], char **envp)
{
	printf("=== DEBUG HANDLE_CHILD_PROCESS START ===\n");
	
	// 1. Redirecionamentos de PIPE
	if (input_fd != STDIN_FILENO)
	{
		printf("DEBUG: Redirecting input from pipe fd %d\n", input_fd);
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(1);
		}
		close(input_fd);
	}
	if (cmd->next)
	{
		printf("DEBUG: Redirecting output to pipe fd %d\n", pipe_fd[1]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

	// 2. Redirecionamentos de ARQUIVO (sobrescrevem pipes)
	printf("DEBUG: Applying file redirections (%d redirections)\n", cmd->redir_count);
	if (!apply_redirections(cmd))
	{
		printf("DEBUG: Redirections failed\n");
		exit(1);
	}
	printf("DEBUG: Redirections applied successfully\n");

	// 3. Executar comando
	printf("DEBUG: Executing command: %s\n", cmd->args[0]->value);
	if (is_builtin(cmd->args))
		exit(exec_builtin(cmd->args, envp));
	else
		exit(execute_external(cmd->args, envp));
	
	printf("=== DEBUG HANDLE_CHILD_PROCESS END ===\n");
}

void	update_fds_after_command(t_command *cmd, t_exec_data *data)
{
	if (*data->input_fd != STDIN_FILENO)
		close(*data->input_fd);
	if (cmd->next)
	{
		close(data->pipe_fd[1]);
		*data->input_fd = data->pipe_fd[0];
	}
	else
		*data->input_fd = STDIN_FILENO;
}
