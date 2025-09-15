/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/15 22:43:41 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*typedef struct s_token_data
{
	t_token	*tokens;
	int		count;
	int		capacity;
}	t_token_data;

typedef struct s_quote_data
{
	char	**token;
	bool	*allow_expand;
}	t_quote_data;*/

static bool	is_special_char(char c)
{
	return (c == '|');
}

static t_token	create_pipe_token(void)
{
	t_token	pipe_token;

	pipe_token.value = ft_strdup("|");
	pipe_token.allow_expand = false;
	pipe_token.is_pipe = true;
	pipe_token.is_redirection = false;
	return (pipe_token);
}

static bool	expand_token_array(t_token_data *data)
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

static bool	process_special_char(char *line, int *i, t_token_data *data)
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

static char	*extract_quoted(const char *line, int *i, bool *allow_expand)
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

static bool	process_quoted_part(char *line, int *i, t_quote_data *qdata)
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

static bool	process_regular_char(char *line, int *i, char **token)
{
	char	*char_str;

	char_str = ft_substr(line, *i, 1);
	if (!char_str)
		return (false);
	*token = ft_strjoin_free(*token, char_str, 3);
	(*i)++;
	return (true);
}

static bool	process_word_chars(char *line, int *i, t_quote_data *qdata)
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

static bool	add_token_to_array(t_token_data *data, char *token, bool allow_expand)
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

static bool	process_word_token(char *line, int *i, t_token_data *data)
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

