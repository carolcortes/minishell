/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ext1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:32:55 by cgross-s          #+#    #+#             */
/*   Updated: 2025/11/24 23:20:16 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*char	*shell_read_line(void)
{
	char	*line;

	line = readline("minishell$> ");
	if (!line)
		return (NULL);
	line = read_multiline_pipe(line);
	return (line);
}*/

char	*shell_read_line(void)
{
	char	*line;

	line = readline("minishell$> ");
	if (!line)
		return (NULL);
	line = read_multiline_pipe(line);
	/* só adicionar ao histórico depois de processar multiline */
	if (line && *line)
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

/*char	*read_multiline_pipe(char *line)
{
	char	*extra;
	char	*joined;

	while (line && ft_strlen(line) > 0
		&& line[ft_strlen(line) - 1] == '|')
	{
		extra = readline("> ");
		if (!extra)
			return (line);
		joined = ft_strjoin(line, extra);
		free(line);
		free(extra);
		line = joined;
	}
	return (line);
}*/

char	*read_multiline_pipe(char *line)
{
	char	*extra;
	char	*tmp;
	char	*joined;

	while (line && ft_strlen(line) > 0
		&& line[ft_strlen(line) - 1] == '|')
	{
		extra = readline("> ");
		if (!extra)
			break ;
		/* garante espaço entre linhas para não colar tokens */
		tmp = ft_strjoin(line, " ");
		joined = ft_strjoin(tmp, extra);
		free(tmp);
		free(line);
		free(extra);
		line = joined;
	}
	return (line);
}
