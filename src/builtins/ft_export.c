/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:12 by cade-oli          #+#    #+#             */
/*   Updated: 2025/12/21 22:35:30 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_valid_identifier(char *str);
static void	print_env_export(char **envp);

/**
 * @brief Add or update an environment variable.
 *
 * Implements the behaviour of the `export` builtin command.
 * If called without arguments, prints an error message.
 * Otherwise, attempts to add or modify an environment variable
 * using the format "KEY=VALUE".
 *
 * @param args Array of tokens (command + variable assignment).
 *             args[0] is "export", args[1] should be "KEY=VALUE".
 * @return 0 on success, 1 on failure.
 */

int	ft_export(t_token **args, char **envp)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_env_export(envp);
		return (0);
	}
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]->value))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n",
				args[i]->value);
			status = 1;
		}
		else if (add_or_update_env(args[i]->value, envp))
			status = 1;
		i++;
	}
	return (status);
}

static void	print_env_export(char **envp)
{
	int		i;
	char	*eq;
	char	*key;
	char	*val;

	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			key = ft_substr(envp[i], 0, eq - envp[i]);
			val = eq + 1;
			if (key)
			{
				printf("declare -x %s=\"%s\"\n", key, val);
				free(key);
			}
		}
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
