/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:32:55 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/16 17:33:59 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*shell_read_line(void)
{
	char	*line;

	line = readline(MAG"🏴‍☠️  minishell 🏴‍☠️ $> "RST);
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("=== TOKENS PARSED ===\n");
	while (tokens[i].value)
	{
		printf("Token %d: '%s' (expand: %d, pipe: %d, redir: %d)\n",
			i, tokens[i].value, tokens[i].allow_expand,
			tokens[i].is_pipe, tokens[i].is_redirection);
		i++;
	}
	printf("=====================\n");
}

void	print_pipeline(t_command *pipeline)
{
	t_command	*cmd;
	int			cmd_index;
	int			i;

	cmd = pipeline;
	cmd_index = 0;
	printf("=== PIPELINE STRUCTURE ===\n");
	while (cmd)
	{
		printf("Command %d: ", cmd_index++);
		i = 0;
		while (i < cmd->argc)
		{
			printf("'%s' ", cmd->args[i]->value);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
	printf("==========================\n");
}
