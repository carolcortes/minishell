/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:18:08 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 16:21:54 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	count_tokens(t_token **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

char	**tokens_to_argv(t_token **tokens)
{
	int		i;
	int		count;
	char	**argv;

	count = count_tokens(tokens);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		argv[i] = ft_strdup(tokens[i]->value);
		if (!argv[i])
		{
			free_argv(argv);
			return (NULL);
		}
		i++;
	}
	argv[count] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
