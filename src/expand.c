/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 17:40:05 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_variables(const char *str, t_shell *shell)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(shell->last_status);
			result = ft_strjoin_free(result, tmp, 3);
			i += 2;
		}
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = handle_env_var(str, &i, result, shell);
		else
			result = handle_literal_char(str, &i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

static t_token	*handle_split(t_token *tokens, int i, char *expanded,
				int *words_added)
{
	int	split_count;

	split_count = count_words(expanded);
	if (split_count > 1)
	{
		tokens = split_token_on_whitespace(tokens, i);
		*words_added = split_count - 1;
		return (tokens);
	}
	tokens[i].allow_expand = false;
	return (tokens);
}

static t_token	*handle_expansion(t_token *tokens, int i, t_shell *shell,
				int *words_added)
{
	char	*expanded;
	char	*original;
	bool	had_var;

	original = tokens[i].value;
	had_var = token_has_variable(original);
	expanded = expand_variables(original, shell);
	if (!expanded)
	{
		printf("Error: memory allocation failed during expansion\n");
		return (tokens);
	}
	free(tokens[i].value);
	tokens[i].value = expanded;
	*words_added = 0;
	if (had_var && expanded[0] != '\0')
		return (handle_split(tokens, i, expanded, words_added));
	else if (expanded[0] != '\0' || !had_var)
		tokens[i].allow_expand = false;
	return (tokens);
}

t_token	*expand_tokens(t_token *tokens, t_shell *shell)
{
	int		i;
	int		words_added;

	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].allow_expand)
		{
			tokens = handle_expansion(tokens, i, shell, &words_added);
			i += words_added;
		}
	}
	remove_empty_expanded_tokens(tokens);
	return (tokens);
}
