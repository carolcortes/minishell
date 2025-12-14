/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:31:20 by cgross-s          #+#    #+#             */
/*   Updated: 2025/12/14 14:34:05 by cgross-s         ###   ########.fr       */
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
}*/

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
		else
		{
			free(tokens[r].value);
			tokens[r].value = NULL;
		}
		r++;
	}
	tokens[w].value = NULL;
}

char	**split_on_whitespace(const char *s)
{
	char	**res;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	return (fill_split(s, res));
}

void	insert_split_tokens(t_token *tokens, int index, char **words)
{
	int		i;
	int		k;

	if (!words || !words[0])
		return ;
	free(tokens[index].value);
	tokens[index].value = words[0];
	tokens[index].quoted = false;
	tokens[index].allow_expand = false;
	k = 1;
	while (words[k])
	{
		i = 0;
		while (tokens[i].value)
			i++;
		tokens[i].value = words[k];
		tokens[i].quoted = false;
		tokens[i].allow_expand = false;
		tokens[i + 1].value = NULL;
		k++;
	}
}
