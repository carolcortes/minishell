/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:22:35 by cgross-s          #+#    #+#             */
/*   Updated: 2025/08/06 23:26:29 by cgross-s         ###   ########.fr       */
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
	printf(Y "Welcome to Minishell!\n" RST);
	printf(G "This is a simple shell implementation.\n" RST);
	printf(C "Type your commands below:\n" RST);
}
