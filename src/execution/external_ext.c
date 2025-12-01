/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:41:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/11/23 18:16:45 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Execute an external program in the child process.
 *
 * Sets child-specific signal handlers, invokes execve(path, argv, envp),
 * and on failure prints an error, frees resources, and exits with an
 * appropriate status (127 for ENOENT, 126 otherwise).
 *
 * Intended to be called in a forked child right before replacing the image.
 *
 * @param path Resolved path to the executable.
 * @param argv Null-terminated argument vector (argv[0] is the program name).
 * @param envp Null-terminated environment array ("KEY=VALUE").
 * @return This function does not return.
 */

void	exec_child(char *path, char **argv, char **envp)
{
	setup_child_signals();
	execve(path, argv, envp);
	perror("minishell");
	free(path);
	free_strings(argv);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

bool	is_assignment(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (str[i] == '=');
}

bool	check_all_assignments(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!is_assignment(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

void	process_assignments(char **argv, t_shell *shell)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		add_or_update_env(argv[i], shell->envp);
		i++;
	}
}

int	handle_empty_command(char **argv)
{
	fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
	free_strings(argv);
	return (127);
}
