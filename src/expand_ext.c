/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 22:48:04 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	token_has_variable(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '?' || ft_isalpha(str[i + 1])
				|| str[i + 1] == '_'))
			return (true);
		i++;
	}
	return (false);
}

/*void	remove_empty_expanded_tokens(t_token *tokens)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].value[0] != '\0' || !tokens[i].allow_expand)
		{
			if (i != j)
			{
				tokens[j] = tokens[i];
				tokens[i].value = NULL;
			}
			j++;
		}
		else
		{
			free(tokens[i].value);
			tokens[i].value = NULL;
		}
	}
	if (j < i)
		tokens[j].value = NULL;
}*/

void remove_empty_expanded_tokens(t_token *tokens)
{
    int i = 0, j = 0;

    while (tokens[i].value)
    {
        //if (tokens[i].value[0] == '\0') // token vazio
		if (tokens[i].value[0] == '\0' && !tokens[i].quoted)
        {
            free(tokens[i].value);
            // shift para a esquerda
            i++;
            continue;
        }
        if (i != j)
            tokens[j] = tokens[i];
        i++;
        j++;
    }
    tokens[j].value = NULL; // termina array
}
