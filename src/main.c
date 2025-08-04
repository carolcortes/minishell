/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/04 23:16:00 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av)
{
	int	status;

	(void)ac;
	if (fork() == 0)
		execvp(av[1], av + 1);
	wait(&status);
	return (EXIT_SUCCESS);
}
