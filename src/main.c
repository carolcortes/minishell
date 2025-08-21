/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/21 22:29:29 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_builtin	g_builtin[] =
{
	{.builtin_name = "exit", .foo = shell_exit},
	{.builtin_name = NULL},
};

char	*shell_read_line(void)
{
	char	*line;

	line = readline("🏴‍☠️ minishell 🏴‍☠️ $> ");
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

int	main(void)
{
	char	*line;
	t_token	*args;
	int		i;

	line = NULL;
	printbanner();
	setup_signals();
	while (1)
	{
		line = shell_read_line();
		if (!line)
			break ;
		args = shell_split_line_quotes(line);
		free(line);
		if (!args)
			continue ;
		expand_tokens(args, 0);
		i = 0;
		while (args[i].value)
		{
			printf("arg[%d]: %s\n", i, args[i].value);
			i++;
		}
		free_tokens(args);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}