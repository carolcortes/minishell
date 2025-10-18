/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 16:10:23 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	len;

	if (!key || !envp)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

//static char	*handle_env_var(const char *str, int *i, char *result)
//var_value = getenv(var_name);
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
	var_value = get_env_value(var_name, shell->envp);
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

//result = handle_env_var(str, &i, result);
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

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].allow_expand)
		{
			expanded = expand_variables(tokens[i].value, shell);
			if (!expanded)
			{
				printf("Error: memory allocation failed during expansion\n");
				return ;
			}
			free(tokens[i].value);
			tokens[i].value = expanded;
		}
		i++;
	}
}
