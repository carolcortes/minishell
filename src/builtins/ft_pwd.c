/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:52 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/30 20:50:19 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Print the current working directory.
 *
 * Implements the behaviour of the `pwd` builtin command.
 * Retrieves the absolute pathname of the current working
 * directory using getcwd() and prints it to standard output.
 *
 * @param args Array of tokens (unused).
 * @return 0 on success, 1 if the current directory
 *         cannot be retrieved.
 */

int	ft_pwd(t_token **args, char **envp)
{
	char	cwd[4096];

	(void)args;
	(void)envp;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
