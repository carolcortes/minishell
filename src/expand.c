/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/12/03 10:27:07 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*handle_env_var(const char *str, int *i, char *result,
				t_shell *shell);
static char	*handle_literal_char(const char *str, int *i, char *result);
static int	append_next(const char *str, int *i, t_shell *shell,
				char **result);

char	*expand_variables(const char *str, t_shell *shell)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
		if (!append_next(str, &i, shell, &result))
			return (NULL);
	return (result);
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (i > 0 && tokens[i - 1].is_redirection
			&& tokens[i - 1].redir_type == 4)
			;
		else if (!tokens[i].quoted)
			expand_single_token(&tokens[i], shell);
		i++;
	}
	remove_empty_expanded_tokens(tokens);
}

static char	*handle_literal_char(const char *str, int *i, char *result)
{
	char	*char_str;

	char_str = ft_substr(str, *i, 1);
	if (!char_str)
		return (NULL);
	result = ft_strjoin_free(result, char_str, 3);
	(*i)++;
	return (result);
}

static char	*handle_env_var(const char *str, int *i, char *result,
	t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*value_dup;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = env_get_value(shell->envp, var_name);
	free(var_name);
	if (var_value)
	{
		value_dup = ft_strdup(var_value);
		if (!value_dup)
			return (NULL);
		result = ft_strjoin_free(result, value_dup, 3);
	}
	return (result);
}

static int	append_next(const char *str, int *i, t_shell *shell,
	char **result)
{
	char	*tmp;

	if (str[*i] == '\\' && str[*i + 1] == '$')
	{
		*result = ft_strjoin_free(*result, ft_strdup("$"), 3);
		*i += 2;
	}
	else if (str[*i] == '$' && str[*i + 1] == '?')
	{
		tmp = ft_itoa(shell->last_status);
		*result = ft_strjoin_free(*result, tmp, 3);
		*i += 2;
	}
	else if (str[*i] == '$' && ft_isdigit(str[*i + 1]))
		*i += 2;
	else if (str[*i] == '$'
		&& (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_'))
		*result = handle_env_var(str, i, *result, shell);
	else
		*result = handle_literal_char(str, i, *result);
	return (*result != NULL);
}
