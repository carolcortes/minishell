/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:58:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/22 23:11:52 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dquote_append_qs(const char *line, int *i, char **result)
{
	char	*tmp;

	tmp = ft_substr(line, *i + 1, 1);
	if (!tmp)
		return (-1);
	*result = ft_strjoin_free(*result, tmp, 3);
	*i += 2;
	if (*result)
		return (1);
	return (-1);
}

int	dquote_append_dollar(const char *line, int *i, char **result)
{
	char	*tmp;

	tmp = ft_substr(line, *i, 2);
	if (!tmp)
		return (-1);
	*result = ft_strjoin_free(*result, tmp, 3);
	*i += 2;
	if (*result)
		return (1);
	return (-1);
}
