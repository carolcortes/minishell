/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:14:15 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/27 14:39:32 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Check and execute a builtin command.
 *
 * Iterates over the builtin table and compares the first token with
 * known builtins. If found, executes the corresponding function.
 *
 * @param args Array of tokens (command + arguments).
 * @return Exit status of the builtin, or 0 if not a builtin.
 */

int	exec_builtin(t_token **args, char **envp)
{
	int				i;
	const t_builtin	builtins[] = {
	{.builtin_name = "echo", .builtin = ft_echo},
	{.builtin_name = "cd", .builtin = ft_cd},
	{.builtin_name = "pwd", .builtin = ft_pwd},
	{.builtin_name = "export", .builtin = ft_export},
	{.builtin_name = "unset", .builtin = ft_unset},
	{.builtin_name = "env", .builtin = ft_env},
	{.builtin_name = "exit", .builtin = ft_exit},
	{.builtin_name = NULL}
	};

	if (!args || !args[0])
		return (0);
	i = 0;
	while (builtins[i].builtin_name)
	{
		if (ft_strcmp(args[0]->value, builtins[i].builtin_name) == 0)
			return (builtins[i].builtin(args, envp));
		i++;
	}
	return (0);
}
