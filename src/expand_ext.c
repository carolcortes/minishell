/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/22 22:40:31 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	token_has_variable(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& (i == 0 || str[i - 1] != '\\')
			&& (str[i + 1] == '?' || ft_isalpha(str[i + 1])
				|| str[i + 1] == '_'))
			return (true);
		i++;
	}
	return (false);
}

void	expand_single_token(t_token *tok, t_shell *shell)
{
	char	*expanded;
	bool	had_var;

	if (!tok->allow_expand)
		return ;
	had_var = token_has_variable(tok->value);
	expanded = expand_variables(tok->value, shell);
	if (!expanded)
	{
		printf("Error: memory allocation failed during expansion\n");
		return ;
	}
	free(tok->value);
	tok->value = expanded;
	if (expanded[0] != '\0' || !had_var)
		tok->allow_expand = false;
}

void	remove_empty_expanded_tokens(t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i].value)
	{
		if (tokens[i].value[0] == '\0' && !tokens[i].quoted)
		{
			free(tokens[i].value);
			i++;
			continue ;
		}
		if (i != j)
			tokens[j] = tokens[i];
		i++;
		j++;
	}
	tokens[j].value = NULL;
}
