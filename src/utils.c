/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:22:35 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/26 17:14:54 by cgross-s         ###   ########.fr       */
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

void	printbanner(void)
{
	printf(G "\nWelcome to\n\t"RED"MINISHELL\n" RST);
	printf(G "\t\ta simple shell implementation.\n\n" RST);
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
