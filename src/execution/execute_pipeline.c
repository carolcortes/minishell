/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/23 10:36:49 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_last_status;

static int	process_command(t_command *cmd, int *input_fd, 
	int pipe_fd[2], pid_t *last_pid, char **envp)
{
	pid_t	pid;

	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		g_last_status = 1;
		return (0);
	}
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, *input_fd, pipe_fd, envp);
	else if (pid < 0)
	{
		perror("minishell: fork");
		g_last_status = 1;
		return (0);
	}
	if (pid > 0)
		*last_pid = pid;
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
		*input_fd = STDIN_FILENO;
	return (1);
}

static void	wait_for_children(pid_t last_pid)
{
	int		status;
	pid_t	waited_pid;

	waited_pid = 1;
	while (waited_pid > 0)
	{
		waited_pid = wait(&status);
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				g_last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_last_status = 128 + WTERMSIG(status);
		}
	}
}

void	execute_pipeline(t_command *pipeline, char **envp)
{
	int			pipe_fd[2];
	int			input_fd;
	t_command	*cmd;
	pid_t		last_pid;

	input_fd = STDIN_FILENO;
	cmd = pipeline;
	last_pid = 0;
	while (cmd)
	{
		if (!process_command(cmd, &input_fd, pipe_fd, &last_pid, envp))
			return ;
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
}
