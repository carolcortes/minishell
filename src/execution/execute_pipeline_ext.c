/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/25 09:27:58 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../inc/minishell.h"

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

void	handle_child_process(t_command *cmd, int input_fd,
	int pipe_fd[2], char **envp)
{
	// REMOVER todos os printf de debug
	// printf("=== CHILD PROCESS: %s ===\n", cmd->args[0]->value);
	// printf("Redirections: %d, Has next: %d\n", ...);
	
	// 1. PRIMEIRO: Redirecionamentos de ARQUIVO
	if (!apply_redirections(cmd))
		exit(1);
	
	// 2. DEPOIS: Redirecionamentos de PIPE
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(1);
		}
		close(input_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

	// 3. Executar comando
	if (is_builtin(cmd->args))
		exit(exec_builtin(cmd->args, envp));
	else
		exit(execute_external(cmd->args, envp));
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
}*/

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

static void	apply_pipe_redirections(int input_fd, int pipe_fd[2],
	t_command *cmd)
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
	if (cmd->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout");
			exit(1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	handle_child_process(t_command *cmd, int input_fd,
	int pipe_fd[2], char **envp)
{
	if (!apply_redirections(cmd))
		exit(1);
	apply_pipe_redirections(input_fd, pipe_fd, cmd);
	if (is_builtin(cmd->args))
		exit(exec_builtin(cmd->args, envp));
	else
		exit(execute_external(cmd->args, envp));
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
