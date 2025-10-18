/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 00:22:08 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_token **args, char **envp)
{
	(void)envp;
	if (!args[1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	if (chdir(args[1]->value) != 0)
	{
		fprintf(stderr, "minishell: cd: %s: %s\n",
			args[1]->value, strerror(errno));
		return (1);
	}
	return (0);
}
