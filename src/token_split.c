/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:15:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 17:25:13 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_total_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens[count].value)
		count++;
	return (count);
}

static void	init_token(t_token *token)
{
	token->value = NULL;
	token->allow_expand = false;
	token->is_pipe = false;
	token->is_redirection = false;
	token->redir_type = 0;
}

static t_token	*create_expanded_array(t_token *tokens, char **words)
{
	t_token	*new_tokens;
	int		total_old;
	int		word_count;
	int		new_size;
	int		i;

	total_old = count_total_tokens(tokens);
	word_count = 0;
	while (words[word_count])
		word_count++;
	new_size = total_old - 1 + word_count + 1;
	new_tokens = malloc(sizeof(t_token) * new_size);
	if (!new_tokens)
		return (NULL);
	i = 0;
	while (i < new_size)
	{
		init_token(&new_tokens[i]);
		i++;
	}
	return (new_tokens);
}

static void	copy_and_insert(t_token *new, t_token *old, int idx, char **words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (old[i].value)
	{
		if (i == idx)
		{
			k = 0;
			while (words[k])
			{
				new[j].value = words[k];
				new[j].allow_expand = false;
				j++;
				k++;
			}
		}
		else
			new[j++] = old[i];
		i++;
	}
}

t_token	*split_token_on_whitespace(t_token *tokens, int index)
{
	char	**words;
	t_token	*new_tokens;

	if (!tokens[index].value || tokens[index].value[0] == '\0')
		return (tokens);
	words = split_on_whitespace(tokens[index].value);
	if (!words || !words[0])
	{
		if (words)
			free(words);
		return (tokens);
	}
	new_tokens = create_expanded_array(tokens, words);
	if (!new_tokens)
	{
		free_strings(words);
		return (tokens);
	}
	copy_and_insert(new_tokens, tokens, index, words);
	free(words);
	free(tokens[index].value);
	free(tokens);
	return (new_tokens);
}
