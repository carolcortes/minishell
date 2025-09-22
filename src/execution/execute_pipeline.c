/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/18 16:38:53 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_last_status;

static int	create_pipe(t_command *cmd, int pipe_fd[2])
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		g_last_status = 1;
		return (1);
	}
	return (0);
}

static int	fork_and_execute(t_command *cmd, t_fork_data *fdata)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, fdata->input_fd, fdata->pipe_fd, fdata->envp);
	else if (pid < 0)
	{
		perror("minishell: fork");
		g_last_status = 1;
		return (1);
	}
	if (pid > 0)
		*fdata->last_pid = pid;
	return (0);
}

static int	process_single_command(t_command *cmd, t_exec_data *data)
{
	t_fork_data	fdata;

	if (create_pipe(cmd, data->pipe_fd))
		return (1);
	fdata.input_fd = *data->input_fd;
	fdata.pipe_fd[0] = data->pipe_fd[0];
	fdata.pipe_fd[1] = data->pipe_fd[1];
	fdata.last_pid = data->last_pid;
	fdata.envp = data->envp;
	if (fork_and_execute(cmd, &fdata))
		return (1);
	update_fds_after_command(cmd, data);
	return (0);
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
	t_exec_data	data;
	t_command	*cmd;
	pid_t		last_pid;
	int			input_fd;

	input_fd = STDIN_FILENO;
	cmd = pipeline;
	last_pid = 0;
	data.input_fd = &input_fd;
	data.last_pid = &last_pid;
	data.envp = envp;
	while (cmd)
	{
		if (process_single_command(cmd, &data))
			return ;
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
}
