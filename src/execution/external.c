/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 18:31:10 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_parent(pid_t pid, char *path, char **argv)
{
	int	status;

	setup_wait_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	free(path);
	free_argv(argv);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	execute_external_command(char *path, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child(path, argv, envp);
	else if (pid > 0)
		return (exec_parent(pid, path, argv));
	perror("minishell: fork");
	free(path);
	free_argv(argv);
	return (1);
}

static int	exec_with_path(char **argv, t_shell *shell)
{
	char	*path;

	if (access(argv[0], F_OK) != 0)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", argv[0]);
		free_argv(argv);
		return (127);
	}
	if (access(argv[0], X_OK) != 0)
	{
		fprintf(stderr, "minishell: %s: Permission denied\n", argv[0]);
		free_argv(argv);
		return (126);
	}
	path = ft_strdup(argv[0]);
	if (!path)
	{
		free_argv(argv);
		return (1);
	}
	return (execute_external_command(path, argv, shell->envp));
}

static int	exec_from_env(char **argv, t_shell *shell)
{
	char	*path;

	path = find_command_path(argv[0], shell->envp);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
		free_argv(argv);
		return (127);
	}
	return (execute_external_command(path, argv, shell->envp));
}

int	execute_external(t_token **args, t_shell *shell)
{
	char	**argv;

	argv = tokens_to_argv(args);
	if (!argv)
		return (1);
	if (ft_strchr(argv[0], '/'))
		return (exec_with_path(argv, shell));
	return (exec_from_env(argv, shell));
}
