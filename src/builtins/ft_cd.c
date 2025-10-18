/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/18 16:52:40 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int	ft_cd(t_token **args, char **envp)
{
	(void)envp;
	if (!args[1])
		return (chdir(getenv("HOME")));
	if (chdir(args[1]->value) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}*/

//Para ficar igual ao bash (resolve erro):
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
