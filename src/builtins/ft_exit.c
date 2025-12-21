/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:58:04 by cade-oli          #+#    #+#             */
/*   Updated: 2025/12/21 18:02:42 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <limits.h>

/**
 * @brief Exit the minishell.
 *
 * Prints "exit", clears readline history, and terminates the program.
 *
 * @param args Unused command arguments.
 * @return This function does not return.
 */

void	cleanup_and_exit(t_command *cmd, t_token *tokens,
		t_shell *shell, int code)
{
	(void)cmd;
	//(void)tokens;
	//(void)shell;
	free_pipeline(shell->first_pipeline_command);
	//free_pipeline(cmd);
	free_tokens(tokens);
	free_strings(shell->envp);
	rl_clear_history();
	exit(code);
}


/* Helper: parse optional sign, update index and sign; return 0 on failure */
static int	parse_sign(const char *s, size_t *i, int *sign)
{
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[(*i)++] == '-')
			*sign = -1;
		if (!s[*i])
			return (0);
	}
	return (1);
}

/* Helper: validate numeric argument and store in *out (<=25 lines) */
static int	is_valid_numeric(const char *s, long *out)
{
	unsigned long	acc;
	int				sign;
	size_t			i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (!parse_sign(s, &i, &sign))
		return (0);
	acc = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		acc = acc * 10 + (s[i] - '0');
		if (acc > (unsigned long)LONG_MAX + (sign < 0))
			return (0);
		i++;
	}
	*out = (long)(sign * (long)acc);
	return (1);
}

/* Helper: print numeric error and exit with 2 */
static void	numeric_error(const char *s)
{
	fprintf(stderr, "minishell: exit: %s: numeric argument required\n", s);
	exit(2);
}

/*
** return >= 0 : normal status
** return <  0 : request shell termination
*/

int	ft_exit(t_token **args, char **envp)
{
	long			val;
	unsigned char	code;
	int				arg_index;

	(void)envp;
	if (!args || !args[0])
		return (-1);
	arg_index = 1;
	if (args[1] && ft_strcmp(args[1]->value, "--") == 0)
		arg_index = 2;
	if (args[arg_index] && args[arg_index + 1]
		&& is_valid_numeric(args[arg_index]->value, &val))
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (args[arg_index])
	{
		if (!is_valid_numeric(args[arg_index]->value, &val))
			numeric_error(args[arg_index]->value);
		code = (unsigned char)val;
		return (-(code + 1));
	}
	return (-1);
}
