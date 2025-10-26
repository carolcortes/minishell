/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/26 18:07:02 by cgross-s         ###   ########.fr       */
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

/*void	remove_empty_expanded_tokens(t_token *tokens)
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
}*/


void	remove_empty_expanded_tokens(t_token *tokens)
{
	int	i;
	int	j;
	bool	prev_is_heredoc;

	i = 0;
	j = 0;
	prev_is_heredoc = false;
	while (tokens[i].value)
	{
		if (prev_is_heredoc)
		{
			// ⚠️ sempre manter o token após '<<' — mesmo se estiver vazio
			tokens[j++] = tokens[i];
			prev_is_heredoc = false;
		}
		else if (tokens[i].is_redirection && tokens[i].redir_type == 4)
		{
			// ⚠️ heredoc redirection — lembrar que o próximo token é especial
			tokens[j++] = tokens[i];
			prev_is_heredoc = true;
		}
		else if (tokens[i].value[0] != '\0')
		{
			// mantém tokens normais não vazios
			tokens[j++] = tokens[i];
		}
		i++;
	}
	tokens[j].value = NULL;
}
