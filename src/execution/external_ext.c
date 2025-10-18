/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:41:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 18:19:37 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_child(char *path, char **argv, char **envp)
{
	setup_child_signals();
	execve(path, argv, envp);
	perror("minishell");
	free(path);
	free_argv(argv);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
