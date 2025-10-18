/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:41:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 16:49:38 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_child(char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	perror("minishell");
	free(path);
	free_argv(argv);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
