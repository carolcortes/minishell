/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/15 14:57:13 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../inc/minishell.h"

int	execute_external(t_token **args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**argv;

	argv = tokens_to_argv(args);
	if (!argv)
		return (1);
	path = find_command_path(argv[0], envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", argv[0]);
		free_argv(argv);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, envp);
		printf("minishell: %s: execution failed\n", argv[0]);
		free(path);
		free_argv(argv);
		exit(126);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("minishell: fork");
		free(path);
		free_argv(argv);
		return (1);
	}
	free(path);
	free_argv(argv);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}
*/

#include "../../inc/minishell.h"

static int	handle_child_process(char *path, char **argv, char **envp)
{
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

static int	execute_command(char *path, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		return (handle_child_process(path, argv, envp));
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(path);
		free_argv(argv);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
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
	return (execute_command(path, argv, envp));
}
