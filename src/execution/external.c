/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/28 13:35:14 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_external_child(char *path, char **argv, char **envp)
{
	setup_child_signals();
	execve(path, argv, envp);
	printf("minishell: %s: execution failed\n", argv[0]);
	free(path);
	free_argv(argv);
	exit(126);
}

static int	handle_fork_error(char *path, char **argv)
{
	perror("minishell: fork");
	free(path);
	free_argv(argv);
	return (1);
}

static int	execute_external_command(char *path, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		return (handle_external_child(path, argv, envp));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(path);
		free_argv(argv);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit (core dumped)\n");
			return (128 + WTERMSIG(status));
		}
		else
			return (1);
	}
	else
		return (handle_fork_error(path, argv));
}

static int	handle_command_not_found(char **argv)
{
	printf("minishell: %s: command not found\n", argv[0]);
	free_argv(argv);
	return (127);
}

int	execute_external(t_token **args, char **envp)
{
	char	*path;
	char	**argv;

	argv = tokens_to_argv(args);
	if (!argv)
		return (1);
	path = find_command_path(argv[0], envp);
	if (!path)
		return (handle_command_not_found(argv));
	return (execute_external_command(path, argv, envp));
}
