/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:26:14 by cgross-s          #+#    #+#             */
/*   Updated: 2025/12/15 23:50:32 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	create_pipe_token(void)
{
	t_token	pipe_token;

	pipe_token.value = ft_strdup("|");
	pipe_token.allow_expand = false;
	pipe_token.is_pipe = true;
	pipe_token.is_redirection = false;
	pipe_token.redir_type = 0;
	//
	pipe_token.quoted = false;
	//
	return (pipe_token);
}

t_token	create_redirection_token(char *value, int type)
{
	t_token	token;

	token.value = ft_strdup(value);
	token.allow_expand = true;
	token.is_pipe = false;
	token.is_redirection = true;
	token.redir_type = type;
	//
	token.quoted = false;
	//
	return (token);
}

/* helpers used by extract_quoted (kept here to respect function limits) */

int	append_one_char_generic(const char *str, int *i, char **result)
{
	char	*one;

	one = ft_substr(str, *i, 1);
	if (!one)
		return (-1);
	*result = ft_strjoin_free(*result, one, 3);
	(*i)++;
	if (*result)
		return (0);
	return (-1);
}

int	dquote_backslash_append(const char *line, int *i, char **result)
{
	if (line[*i] != '\\' || !line[*i + 1])
		return (0);
	if (line[*i + 1] == '"' || line[*i + 1] == '\\')
		return (dquote_append_qs(line, i, result));
	if (line[*i + 1] == '$')
		return (dquote_append_dollar(line, i, result));
	return (0);
}

char	*extract_quoted_loop(const char *line, int *i, char quote, char *result)
{
	int	ret;

	while (line[*i])
	{
		if (line[*i] == quote)
		{
			(*i)++;
			return (result);
		}
		if (quote == '"')
		{
			ret = dquote_backslash_append(line, i, &result);
			if (ret == 1)
				continue ;
			if (ret == -1)
				return (free(result), NULL);
		}
		if (append_one_char_generic(line, i, &result) == -1)
			return (free(result), NULL);
	}
	return (free(result), NULL);
}
