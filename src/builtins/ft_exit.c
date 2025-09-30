/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:58:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/30 20:49:27 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Exit the minishell.
 *
 * Prints "exit", clears readline history, and terminates the program.
 *
 * @param args Unused command arguments.
 * @return This function does not return.
 */

int	ft_exit(t_token **args, char **envp)
{
	(void)envp;
	(void)args;
	printf(C "Good bye! 👋\n" RST);
	rl_clear_history();
	exit(0);
}
