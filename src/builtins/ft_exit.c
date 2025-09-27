/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:58:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/27 14:50:14 by cade-oli         ###   ########.fr       */
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

// int	ft_exit(t_token **args, char **envp, int exit_code)
int	ft_exit(t_token **args, char **envp)
{
	// unsigned char	value; // TO DO, store exit code in a byte so it loops around
	(void)envp;
	(void)args;
	// value = exit_code;
	printf(C "Good bye! 👋\n" RST);
	rl_clear_history();
	exit(0);
}
