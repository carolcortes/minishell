/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/12 20:31:34 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*4 functions*/

static char	*handle_env_var(const char *str, int *i, char *result)
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
	var_value = getenv(var_name);
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

/*static char	*expand_variables(const char *str, int last_status)
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
			//tmp = ft_itoa(last_status);
			tmp = ft_itoa(g_last_status); // ✅ Pega o último status
			result = ft_strjoin_free(result, tmp, 3);
			i += 2;
		}
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = handle_env_var(str, &i, result);
		else
			result = handle_literal_char(str, &i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}*/

// Na função expand_variables(), você precisa USAR o last_status
static char *expand_variables(const char *str, int last_status)
{
    int     i;
    char    *result;
    char    *tmp;

    i = 0;
    result = ft_strdup("");
    if (!result)
        return (NULL);
    
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
        {
            // ✅ AGORA USA last_status!
            tmp = ft_itoa(last_status);
            result = ft_strjoin_free(result, tmp, 3);
            i += 2;
        }
        else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
        {
            result = handle_env_var(str, &i, result);
        }
        else
        {
            result = handle_literal_char(str, &i, result);
        }
        if (!result)
            return (NULL);
    }
    return (result);
}

/*void	expand_tokens(t_token *tokens, int last_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].allow_expand)
		{
			expanded = expand_variables(tokens[i].value, last_status);
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
}*/

// Na função expand_tokens(), passe o last_status corretamente:
void expand_tokens(t_token *tokens, int last_status)
{
    int     i;
    char    *expanded;

    i = 0;
    while (tokens[i].value)
    {
        if (tokens[i].allow_expand)
        {
            // ✅ Passa last_status para a função
            expanded = expand_variables(tokens[i].value, last_status);
            if (!expanded)
            {
                printf("Error: memory allocation failed during expansion\n");
                return;
            }
            free(tokens[i].value);
            tokens[i].value = expanded;
        }
        i++;
    }
}

