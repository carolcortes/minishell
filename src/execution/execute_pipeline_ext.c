/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/15 16:50:28 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// extern int	g_last_status;

//static void	redirect_input(int input_fd)
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

//static void	redirect_output(int pipe_fd[2])
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

//static void	execute_command(t_command *cmd, char **envp)
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

//static void	handle_child_process(t_command *cmd, int input_fd,
//	int pipe_fd[2], char **envp)
void	handle_child_process(t_command *cmd, int input_fd,
	int pipe_fd[2], char **envp)
{
	redirect_input(input_fd);
	if (cmd->next)
		redirect_output(pipe_fd);
	execute_command(cmd, envp);
}

//static void	update_fds_after_command(t_command *cmd, t_exec_data *data)
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
