/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/08/22 19:01:50 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*7 functions*/

bool	is_spaces(char c)
{
	int	i;

	i = 0;
	while (WHITESPACES[i])
	{
		if (c == WHITESPACES[i])
			return (true);
		i++;
	}
	return (false);
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

void	free_tokens(t_token *tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

bool	process_quoted_part(char *line, int *i, char **token, bool *allow_expand)
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
		*allow_expand = false;
	*token = ft_strjoin_free(*token, part, 3);
	return (true);
}

bool	process_regular_char(char *line, int *i, char **token)
{
	char	*part;

	part = ft_substr(line, *i, 1);
	if (!part)
		return (false);
	*token = ft_strjoin_free(*token, part, 3);
	(*i)++;
	return (true);
}

bool	process_token(char *line, int *i, t_token **tokens, int *count, int *capacity)
{
	char	*token;
	bool	allow_expand;
	t_token	*new_tokens;

	token = ft_strdup("");
	allow_expand = true;
	if (!token)
		return (false);
	while (line[*i] && !is_spaces(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (!process_quoted_part(line, i, &token, &allow_expand))
				return (free(token), false);
		}
		else
		{
			if (!process_regular_char(line, i, &token))
				return (free(token), false);
		}
	}
	if (*count >= *capacity - 1)
	{
		*capacity *= 2;
		new_tokens = realloc(*tokens, sizeof(t_token) * (*capacity));
		if (!new_tokens)
			return (free(token), false);
		*tokens = new_tokens;
	}
	(*tokens)[*count].value = token;
	(*tokens)[*count].allow_expand = allow_expand;
	(*count)++;
	return (true);
}

t_token	*shell_split_line_quotes(char *line)
{
	int		i;
	int		count;
	int		capacity;
	t_token	*tokens;

	i = 0;
	count = 0;
	capacity = 8;
	tokens = malloc(sizeof(t_token) * capacity);
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		while (line[i] && is_spaces(line[i]))
			i++;
		if (!line[i])
			break ;
		if (!process_token(line, &i, &tokens, &count, &capacity))
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	tokens[count].value = NULL;
	tokens[count].allow_expand = false;
	return (tokens);
}
