/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:18:08 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/21 22:19:56 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Execution helpers: builtin detection and argv conversion.
 *
 * is_builtin: checks if args[0] is a shell builtin
 *             (echo, cd, pwd, export, unset, env, exit).
 * tokens_to_argv: duplicates a NULL-terminated token list into a malloc'd argv.
 *
 */

bool	is_builtin(t_token **args)
{
	int			i;
	const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(args[0]->value, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	**tokens_to_argv(t_token **tokens)
{
	int		i;
	int		count;
	char	**argv;

	count = get_token_count(tokens);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		argv[i] = ft_strdup(tokens[i]->value);
		if (!argv[i])
		{
			free_strings(argv);
			return (NULL);
		}
		i++;
	}
	argv[count] = NULL;
	return (argv);
}
