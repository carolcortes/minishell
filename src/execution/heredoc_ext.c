/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:28:41 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/20 22:39:54 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var_value(char *name, t_shell *shell)
{
	char	*val;

	val = get_env_var_value(name, shell);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*expand_braced_var(const char *str, size_t *i, t_shell *shell)
{
	char	*name;
	char	*val;
	size_t	start;
	char	*res;

	res = ft_strdup("");
	start = ++(*i);
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] == '}')
	{
		name = ft_substr(str, start, *i - start);
		val = get_var_value(name, shell);
		res = ft_strjoin_free(res, val, 3);
		free(name);
		(*i)++;
	}
	else
		res = ft_strjoin_free(res, ft_strdup("${"), 3);
	return (res);
}

char	*expand_simple_var(const char *str, size_t *i, t_shell *shell)
{
	size_t	start;
	char	*name;
	char	*val;
	char	*res;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	name = ft_substr(str, start, *i - start);
	val = get_var_value(name, shell);
	res = ft_strdup(val);
	free(val);
	free(name);
	return (res);
}

void	append_char(char **res, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strdup(buf);
	*res = ft_strjoin_free(*res, tmp, 3);
}
