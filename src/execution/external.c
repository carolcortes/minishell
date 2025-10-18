/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/12 17:08:38 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <errno.h>

static void	exec_child(char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	perror("minishell");
	free(path);
	free_argv(argv);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

static int	exec_parent(pid_t pid, char *path, char **argv)
{
	int	status;

	waitpid(pid, &status, 0);
	free(path);
	free_argv(argv);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
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

//int	execute_external(t_token **args, char **envp)
int	execute_external(t_token **args, t_shell *shell)
{
	char	*path;
	char	**argv;

	argv = tokens_to_argv(args);
	if (!argv)
		return (1);

	path = find_command_path(argv[0], shell->envp);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", argv[0]);
		free_argv(argv);
		return (127);
	}
	if (ft_strcmp(path, "PERMISSION_DENIED") == 0)
	{
		fprintf(stderr, "minishell: %s: Permission denied\n", argv[0]);
		free(path);
		free_argv(argv);
		return (126);
	}
	return (execute_external_command(path, argv, shell->envp));
}
