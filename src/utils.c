/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:22:35 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/21 22:19:32 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_getcwd(char *buf, size_t size)
{
	if (getcwd(buf, size) == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
}

bool	is_spaces(char c)
{
	int	i;

	i = 0;
	while (WHITESPACES[i])
	{
		if (c == WHITESPACES[i])
			return (true);
		i++;
	}
	return (false);
}

int	get_token_count(t_token **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}
