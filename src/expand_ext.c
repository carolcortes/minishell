/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/11/16 00:04:23 by cgross-s         ###   ########.fr       */
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
	int		r;
	int		w;
	bool	is_delimiter;

	r = 0;
	w = 0;
	while (tokens[r].value)
	{
		is_delimiter = (r > 0
				&& tokens[r - 1].is_redirection
				&& tokens[r - 1].redir_type == 4);
		if (is_delimiter || tokens[r].value[0] != '\0')
		{
			tokens[w] = tokens[r];
			w++;
		}
		r++;
	}
	tokens[w].value = NULL;
}
