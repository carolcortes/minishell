/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:21:29 by cade-oli          #+#    #+#             */
/*   Updated: 2024/11/13 10:28:28 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		count_tokens(char const *s, char c);
char	*fill_position(char const *s, int start, int end);
void	*free_position(char **strs, int count);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	int		i_token;
	char	**result;

	result = ft_calloc(count_tokens(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	result[count_tokens(s, c)] = NULL;
	j = -1;
	i = -1;
	i_token = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && i_token < 0)
			i_token = i;
		else if ((s[i] == c || i == ft_strlen(s)) && i_token >= 0)
		{
			result[++j] = fill_position(s, i_token, i);
			if (!(result[j]))
				return (free_position(result, j));
			i_token = -1;
		}
	}
	return (result);
}

int	count_tokens(char const *s, char c)
{
	int	count;
	int	is_token;

	is_token = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && is_token == 0)
		{
			is_token = 1;
			count++;
		}
		else if (*s == c)
			is_token = 0;
		s++;
	}
	return (count);
}

char	*fill_position(char const *s, int start, int end)
{
	char	*token;
	int		i;

	i = 0;
	token = malloc((end - start + 1) * sizeof(char));
	if (!token)
		return (NULL);
	while (start < end)
		token[i++] = s[start++];
	token[i] = '\0';
	return (token);
}

void	*free_position(char **strs, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(strs[i]);
	free(strs);
	return (NULL);
}
