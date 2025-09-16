/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:50:13 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/16 15:56:41 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_special_char(char c)
{
	return (c == '|');
}

t_token	create_pipe_token(void)
{
	t_token	pipe_token;

	pipe_token.value = ft_strdup("|");
	pipe_token.allow_expand = false;
	pipe_token.is_pipe = true;
	pipe_token.is_redirection = false;
	return (pipe_token);
}

bool	expand_token_array(t_token_data *data)
{
	t_token	*new_tokens;
	int		new_capacity;

	new_capacity = data->capacity * 2;
	new_tokens = realloc(data->tokens, sizeof(t_token) * new_capacity);
	if (!new_tokens)
		return (false);
	data->tokens = new_tokens;
	data->capacity = new_capacity;
	return (true);
}

bool	process_special_char(char *line, int *i, t_token_data *data)
{
	t_token	special_token;

	if (line[*i] == '|')
		special_token = create_pipe_token();
	else
	{
		(*i)++;
		return (true);
	}
	if (data->count >= data->capacity - 1 && !expand_token_array(data))
		return (false);
	data->tokens[data->count] = special_token;
	data->count++;
	(*i)++;
	return (true);
}

char	*extract_quoted(const char *line, int *i, bool *allow_expand)
{
	char	quote;
	int		start;
	char	*result;

	quote = line[*i];
	if (quote == '\'')
		*allow_expand = false;
	else if (quote == '"')
		*allow_expand = true;
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (NULL);
	result = ft_substr(line, start, *i - start);
	(*i)++;
	return (result);
}
