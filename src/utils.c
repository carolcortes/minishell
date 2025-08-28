/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:22:35 by cgross-s          #+#    #+#             */
/*   Updated: 2025/08/28 22:50:55 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*3 functions*/

void	ft_getcwd(char *buf, size_t size)
{
	if (getcwd(buf, size) == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
}

void	printbanner(void)
{
	printf(Y "Welcome to Minishell!\n" RST);
	printf(G "This is a simple shell implementation.\n" RST);
	printf(C "Type your commands below:\n" RST);
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
