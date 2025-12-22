/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/12/21 22:28:32 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	create_pipe_and_fork(t_command *cmd, int pipe_fd[2], pid_t *pid,
				t_shell *shell);
static void	update_file_descriptors(int *input_fd, int pipe_fd[2],
				t_command *cmd);
static int	process_command(t_command *cmd, t_process_data *data,
				t_shell *shell, t_token *tokens);
static void	wait_for_children(pid_t last_pid, t_shell *shell);

/**
 * @brief Orchestrate execution of a command pipeline.
 *
 * Creates pipes between consecutive commands, forks a process per stage, and
 * wires stdin/stdout appropriately. In children, applies redirections and
 * executes either a builtin or an external command. The parent closes unused
 * FDs, tracks the last command's PID, and waits for all children.
 *
 * Updates shell->last_status based on the last command's exit status or
 * terminating signal. On pipe/fork errors, sets shell->last_status to 1.
 *
 * @param pipeline Head of the parsed command list (linked via cmd->next).
 * @param shell Shell state (environment, last_status, and signal handling).
*/

void	execute_pipeline(t_command *pipeline, t_shell *shell, t_token *tokens)
{
	t_process_data	data;
	int				input_fd;
	t_command		*cmd;
	pid_t			last_pid;

	input_fd = STDIN_FILENO;
	shell->first_pipeline_command = pipeline;
	cmd = pipeline;
	last_pid = 0;
	data.input_fd = &input_fd;
	data.last_pid = &last_pid;
	while (cmd)
	{
		if (!process_command(cmd, &data, shell, tokens))
			return ;
		cmd = cmd->next;
	}
	wait_for_children(last_pid, shell);
}

static int	create_pipe_and_fork(t_command *cmd, int pipe_fd[2], pid_t *pid,
	t_shell *shell)
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		shell->last_status = 1;
		return (0);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork");
		shell->last_status = 1;
		return (0);
	}
	return (1);
}

static void	update_file_descriptors(int *input_fd, int pipe_fd[2],
	t_command *cmd)
{
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
		*input_fd = STDIN_FILENO;
}

static int	process_command(t_command *cmd, t_process_data *data,
	t_shell *shell, t_token *tokens)
{
	pid_t	pid;

	if (!create_pipe_and_fork(cmd, data->pipe_fd, &pid, shell))
		return (0);
	if (pid == 0)
	{
		setup_child_signals();
		handle_child_process(cmd, data, shell, tokens);
	}
	if (pid > 0)
		*data->last_pid = pid;
	update_file_descriptors(data->input_fd, data->pipe_fd, cmd);
	return (1);
}

static void	wait_for_children(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	waited_pid;

	setup_wait_signals();
	waited_pid = 1;
	while (waited_pid > 0)
	{
		waited_pid = wait(&status);
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
				shell->last_status = 128 + WTERMSIG(status);
			}
		}
		setup_signals();
	}
}
