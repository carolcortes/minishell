/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/03 22:09:17 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_token **args)
{
	if (!args[1])
		return (chdir(getenv("HOME")));
	if (chdir(args[1]->value) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
