/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pip_ext1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:03:36 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/12 17:08:05 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

//void	handle_child_process(t_command *cmd, int input_fd,
//	int pipe_fd[2], char **env)
void	handle_child_process(t_command *cmd, int input_fd,
	int pipe_fd[2], t_shell *shell)
{
	if (!apply_redirections(cmd))
		exit(1);
	apply_pipe_redirections(input_fd, pipe_fd, cmd);
	if (is_builtin(cmd->args))
		//exit(exec_builtin(cmd->args, env));
		exit(exec_builtin(cmd->args, shell->envp));
	else
		//exit(execute_external(cmd->args, env));
		//exit(execute_external(cmd->args, shell->envp));
		exit(execute_external(cmd->args, shell));
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
