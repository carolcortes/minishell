/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:15:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 17:21:17 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*extract_word(const char *str, int *index)
{
	int		start;
	char	*word;

	while (str[*index] && is_spaces(str[*index]))
		(*index)++;
	start = *index;
	while (str[*index] && !is_spaces(str[*index]))
		(*index)++;
	word = ft_substr(str, start, *index - start);
	return (word);
}

char	**split_on_whitespace(const char *str)
{
	char	**words;
	int		word_count;
	int		i;
	int		j;

	word_count = count_words(str);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		words[j] = extract_word(str, &i);
		if (!words[j])
		{
			while (--j >= 0)
				free(words[j]);
			return (free(words), NULL);
		}
		j++;
	}
	words[j] = NULL;
	return (words);
}
