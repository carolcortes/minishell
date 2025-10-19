/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:15:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 13:33:54 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_parent(pid_t pid, char *path, char **argv);
static int	execute_external_command(char *path, char **argv, char **envp);
static int	exec_with_path(char **argv, t_shell *shell);
static int	exec_from_env(char **argv, t_shell *shell);

/**
 * @brief Launch an external command.
 *
 * Converts parsed tokens to argv, resolves the executable either from an
 * explicit path (contains '/') or by searching PATH, validates existence and
 * execute permission, then forks and executes the program. The parent waits,
 * maps termination to shell status codes, and frees resources.
 *
 * Exit codes:
 * - 127: command not found or No such file or directory
 * - 126: permission denied or exec error but file exists
 * - 128 + signal: terminated by a signal (prints for SIGINT/SIGQUIT)
 * - otherwise: child's normal exit status
 *
 * @param args Token list for the command (args[0] is the program name).
 * @param shell Shell state providing envp and signal handling.
 * @return Final status code to store in shell->last_status.
 */

int	execute_external(t_token **args, t_shell *shell)
{
	char	**argv;

	argv = tokens_to_argv(args);
	if (!argv)
		return (1);
	if (argv[0][0] == '\0')
	{
		fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
		free_strings(argv);
		return (127);
	}
	if (ft_strchr(argv[0], '/'))
		return (exec_with_path(argv, shell));
	return (exec_from_env(argv, shell));
}

static int	exec_parent(pid_t pid, char *path, char **argv)
{
	int	status;

	setup_wait_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	free(path);
	free_strings(argv);
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
	free_strings(argv);
	return (1);
}

static int	exec_with_path(char **argv, t_shell *shell)
{
	char		*path;
	struct stat	path_stat;

	if (access(argv[0], F_OK) != 0)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", argv[0]);
		return (free_strings(argv), 127);
	}
	if (stat(argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", argv[0]);
		return (free_strings(argv), 126);
	}
	if (access(argv[0], X_OK) != 0)
	{
		fprintf(stderr, "minishell: %s: Permission denied\n", argv[0]);
		free_strings(argv);
		return (126);
	}
	path = ft_strdup(argv[0]);
	if (!path)
		return (free_strings(argv), 1);
	return (execute_external_command(path, argv, shell->envp));
}

static int	exec_from_env(char **argv, t_shell *shell)
{
	char	*path;

	path = find_command_path(argv[0], shell->envp);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
		free_strings(argv);
		return (127);
	}
	return (execute_external_command(path, argv, shell->envp));
}
