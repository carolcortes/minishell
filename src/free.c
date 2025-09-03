/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:35:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/28 22:51:00 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].value)
		free(tokens[i++].value);
	free(tokens);
}

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (result);
}
