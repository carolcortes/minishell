/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:18 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/22 18:14:42 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Print arguments to standard output.
 *
 * Implements the behaviour of the `echo` builtin command.
 * Prints all arguments separated by a single space. If the first
 * argument is "-n", the trailing newline is suppressed. Works with
 * a token array of structs (t_token*) passed by address (t_token**).
 *
 * @param args Address of the token array (command + arguments).
 *             (*args)[0].value is "echo"; (*args)[1..].value are args.
 * @return Always returns 0 (success).
 */

/*int	ft_echo(t_token **args)
{
	int		i;
	int		newline;

	if (!args || !*args)
		return (1);
	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1]->value, "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]->value);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}*/

static void	print_with_slash_interpretation(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i++;
			if (str[i] == 'n')
				printf("\n");
			else if (str[i] == 't')
				printf("\t");
			else if (str[i] == '\\')
				printf("\\");
			else
				printf("\\%c", str[i]);
		}
		else
		{
			printf("%c", str[i]);
		}
		i++;
	}
}

int	ft_echo(t_token **args)
{
	int		i;
	int		newline;
	int		interpret_slash;

	if (!args || !args[0])
		return (1);
	
	i = 1;
	newline = 1;
	interpret_slash = 0;
	
	// Processar opções
	while (args[i] && args[i]->value[0] == '-')
	{
		if (ft_strcmp(args[i]->value, "-n") == 0)
		{
			newline = 0;
			i++;
		}
		else if (ft_strcmp(args[i]->value, "-e") == 0)
		{
			interpret_slash = 1;
			i++;
		}
		else if (ft_strcmp(args[i]->value, "-E") == 0)
		{
			interpret_slash = 0;
			i++;
		}
		else
		{
			break;
		}
	}
	
	// Imprimir argumentos
	while (args[i])
	{
		if (interpret_slash)
			print_with_slash_interpretation(args[i]->value);
		else
			printf("%s", args[i]->value);
		
		if (args[i + 1])
			printf(" ");
		i++;
	}
	
	if (newline)
		printf("\n");
	return (0);
}
