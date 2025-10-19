/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:41:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 20:34:00 by cade-oli         ###   ########.fr       */
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
