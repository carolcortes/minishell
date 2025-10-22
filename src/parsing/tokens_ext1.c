/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:50:13 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/22 22:50:01 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static t_token	handle_redirection_token(char *line, int *i)
{
	t_token	special_token;
	char	next_char;

	special_token.value = NULL;
	special_token.allow_expand = false;
	special_token.is_pipe = false;
	special_token.is_redirection = false;
	special_token.redir_type = 0;
	next_char = line[*i + 1];
	if (line[*i] == '>' && next_char == '>')
	{
		special_token = create_redirection_token(">>", 2);
		(*i)++;
	}
	else if (line[*i] == '>')
		special_token = create_redirection_token(">", 1);
	else if (line[*i] == '<' && next_char == '<')
	{
		special_token = create_redirection_token("<<", 4);
		(*i)++;
	}
	else if (line[*i] == '<')
		special_token = create_redirection_token("<", 3);
	return (special_token);
}

static bool	add_special_token(t_token_data *data, t_token special_token)
{
	if (data->count >= data->capacity - 1 && !expand_token_array(data))
		return (false);
	data->tokens[data->count] = special_token;
	data->count++;
	return (true);
}

bool	process_special_char(char *line, int *i, t_token_data *data)
{
	t_token	special_token;

	if (line[*i] == '|')
		special_token = create_pipe_token();
	else if (line[*i] == '>' || line[*i] == '<')
		special_token = handle_redirection_token(line, i);
	else
	{
		(*i)++;
		return (true);
	}
	if (!add_special_token(data, special_token))
		return (false);
	(*i)++;
	return (true);
}

char	*extract_quoted(const char *line, int *i, bool *allow_expand,
	bool *quoted)
{
	char	quote;
	char	*result;

	quote = line[*i];
	*allow_expand = (quote == '"');
	*quoted = true;
	(*i)++;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (extract_quoted_loop(line, i, quote, result));
}
