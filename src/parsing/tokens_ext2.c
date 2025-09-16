/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:01:43 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/16 16:03:28 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	process_quoted_part(char *line, int *i, t_quote_data *qdata)
{
	bool	local_expand;
	char	*part;

	part = extract_quoted(line, i, &local_expand);
	if (!part)
	{
		printf("Syntax error: unclosed quote\n");
		return (false);
	}
	if (!local_expand)
		*qdata->allow_expand = false;
	*qdata->token = ft_strjoin_free(*qdata->token, part, 3);
	return (true);
}

bool	process_regular_char(char *line, int *i, char **token)
{
	char	*char_str;

	char_str = ft_substr(line, *i, 1);
	if (!char_str)
		return (false);
	*token = ft_strjoin_free(*token, char_str, 3);
	(*i)++;
	return (true);
}

bool	process_word_chars(char *line, int *i, t_quote_data *qdata)
{
	while (line[*i] && !is_spaces(line[*i]) && !is_special_char(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (!process_quoted_part(line, i, qdata))
				return (false);
		}
		else
		{
			if (!process_regular_char(line, i, qdata->token))
				return (false);
		}
	}
	return (true);
}

bool	add_token_to_array(t_token_data *data, char *token, bool allow_expand)
{
	if (data->count >= data->capacity - 1)
	{
		if (!expand_token_array(data))
			return (false);
	}
	data->tokens[data->count].value = token;
	data->tokens[data->count].allow_expand = allow_expand;
	data->tokens[data->count].is_pipe = false;
	data->tokens[data->count].is_redirection = false;
	data->count++;
	return (true);
}

bool	process_word_token(char *line, int *i, t_token_data *data)
{
	char		*token;
	bool		allow_expand;
	t_quote_data	qdata;

	token = ft_strdup("");
	allow_expand = true;
	if (!token)
		return (false);
	qdata.token = &token;
	qdata.allow_expand = &allow_expand;
	if (!process_word_chars(line, i, &qdata))
		return (free(token), false);
	if (!add_token_to_array(data, token, allow_expand))
		return (free(token), false);
	return (true);
}
