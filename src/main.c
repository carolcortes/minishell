/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/28 22:10:30 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*3 functions*/

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

	line = NULL;
	printbanner();
	setup_signals();
	while (42)
	{
		line = shell_read_line();
		if (!line)
			break ;
		args = shell_split_line_quotes(line);
		free(line);
		if (!args)
			continue ;
		expand_tokens(args, 0);
		if (args[0].value)
		{
			if (!exec_builtin(&args))
				printf("comando externo: %s\n", args[0].value);
			// não é builtin → TO DO: executar comando externo
		}
		free_tokens(args);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
