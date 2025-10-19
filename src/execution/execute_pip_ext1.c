/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pip_ext1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:03:36 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 17:55:26 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	apply_pipe_redirections(int input_fd, int pipe_fd[2],
				t_command *cmd);

/**
 * @brief Execute a single pipeline stage in a child process.
 *
 * Implements the child-side setup for pipeline execution: applies file
 * redirections, connects stdin/stdout to the proper pipe ends, and dispatches
 * either a builtin or an external command.
 *
 * @param cmd Parsed command for this pipeline stage.
 * @param input_fd File descriptor to use as stdin (read end from previous
 *                 stage or STDIN_FILENO for the first stage).
 * @param pipe_fd Pair of pipe FDs for this stage. If there is a next command,
 *                pipe_fd[1] becomes stdout; otherwise both ends are closed.
 * @param shell Shell state and environment used to execute the command.
 * @return This function does not return; it exits with the command’s status.
*/

void	handle_child_process(t_command *cmd, t_process_data *data,
	t_shell *shell, t_token *tokens)
{
	int input_fd;
	int pipe_fd[2];

	input_fd = *data->input_fd;
	pipe_fd[0] = data->pipe_fd[0];
	pipe_fd[1] = data->pipe_fd[1];
	apply_pipe_redirections(input_fd, pipe_fd, cmd);
	if (!apply_redirections(cmd, shell, tokens))
		exit(1);
	if (is_builtin(cmd->args))
		exit(exec_builtin(cmd->args, shell->envp));
	else
		exit(execute_external(cmd->args, shell));
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
