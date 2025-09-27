/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/23 11:33:11 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	initialize_tokens_array(t_token *tokens, int capacity)
{
	int	i;

	i = 0;
	while (i < capacity)
	{
		tokens[i].value = NULL;
		tokens[i].allow_expand = false;
		tokens[i].is_pipe = false;
		tokens[i].is_redirection = false;
		i++;
	}
}

static bool	process_line_characters(char *line, int *i, t_token_data *data)
{
	while (line[*i] && is_spaces(line[*i]))
		(*i)++;
	if (!line[*i])
		return (true);
	if (is_special_char(line[*i]))
	{
		if (!process_special_char(line, i, data))
			return (false);
	}
	else
	{
		if (!process_word_token(line, i, data))
			return (false);
	}
	return (true);
}

static bool	initialize_parsing(t_token_data *data)
{
	data->capacity = 8;
	data->tokens = malloc(sizeof(t_token) * data->capacity);
	if (!data->tokens)
		return (false);
	initialize_tokens_array(data->tokens, data->capacity);
	data->count = 0;
	return (true);
}

static bool	process_entire_line(char *line, t_token_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!process_line_characters(line, &i, data))
			return (false);
	}
	return (true);
}

t_token	*shell_split_line_quotes(char *line)
{
	t_token_data	data;
	t_token			*tokens;

	if (!initialize_parsing(&data))
		return (NULL);
	if (!process_entire_line(line, &data))
	{
		free_tokens(data.tokens);
		return (NULL);
	}
	tokens = data.tokens;
	tokens[data.count].value = NULL;
	tokens[data.count].allow_expand = false;
	tokens[data.count].is_pipe = false;
	tokens[data.count].is_redirection = false;
	return (tokens);
}
