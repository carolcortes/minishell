/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:32:18 by cgross-s          #+#    #+#             */
/*   Updated: 2025/12/15 23:32:31 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_words(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !ft_isspace(s[i]))
				i++;
		}
	}
	return (count);
}

char	**fill_split(const char *s, char **res)
{
	int	i;
	int	start;
	int	idx;

	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		res[idx++] = ft_substr(s, start, i - start);
	}
	res[idx] = NULL;
	return (res);
}

int	skip_heredoc(t_token *tokens, int i)
{
	if (i > 0 && tokens[i - 1].is_redirection
		&& tokens[i - 1].redir_type == 4)
		return (1);
	return (0);
}

void	handle_expansion(t_token *token, t_shell *shell)
{
	if (token->allow_expand)
		expand_single_token(token, shell);
}

void	split_and_insert(t_token *tokens, int i)
{
	char	**words;

	//if (tokens[i].quoted || !tokens[i].value)
	if (!tokens[i].value || tokens[i].quoted)
		return ;
	if (!ft_strchr(tokens[i].value, ' '))
		return ;
	words = split_on_whitespace(tokens[i].value);
	if (!words)
		return ;
	insert_split_tokens(tokens, i, words);
	free(words);
}
