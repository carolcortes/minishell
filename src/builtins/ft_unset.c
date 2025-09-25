/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:22 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/25 20:42:50 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Remove an environment variable.
 *
 * Implements the behaviour of the `unset` builtin command.
 * Removes the variable specified by the argument from the
 * environment. If no argument is provided, prints an error.
 *
 * @param args Array of tokens (command + variable name).
 *             args[0] is "unset", args[1] is the variable name.
 * @return 0 on success, 1 if no argument is given or
 *         if the variable could not be removed.
 */

//int	ft_unset(t_token **args)
/*int	ft_unset(t_token **args, char **envp)
{
	(void)envp; // ✅ Marcar como não usado
	if (!args[1])
	{
		printf("unset: precisa de argumento\n");
		return (1);
	}
	if (unsetenv(args[1]->value) != 0)
	{
		perror("unset");
		return (1);
	}
	return (0);
}*/

/*static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	remove_variable_from_env(char *var, char ***envp)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, ft_strlen(var)) != 0
			|| ((*envp)[i][ft_strlen(var)] != '='
			&& (*envp)[i][ft_strlen(var)] != '\0'))
		{
			new_env[j] = ft_strdup((*envp)[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_env(*envp);
	*envp = new_env;
}

int	ft_unset(t_token **args, char ***envp)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]->value))
		{
			printf("unset: '%s': not a valid identifier\n", args[i]->value);
			exit_status = 1;
		}
		else
		{
			remove_variable_from_env(args[i]->value, envp);
		}
		i++;
	}
	return (exit_status);
}*/

/*static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	remove_variable_from_env(char *var, char **envp)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) != 0
			|| (envp[i][ft_strlen(var)] != '='
			&& envp[i][ft_strlen(var)] != '\0'))
		{
			new_env[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_env(envp);
	envp = new_env; // ⚠️ Isso não vai funcionar - precisa retornar o novo array
}

int	ft_unset(t_token **args, char **envp)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]->value))
		{
			printf("unset: '%s': not a valid identifier\n", args[i]->value);
			exit_status = 1;
		}
		else
		{
			// ⚠️ remove_variable_from_env não funciona com char **
			// porque não pode modificar o ponteiro original
			unsetenv(args[i]->value); // Usar unsetenv do sistema
		}
		i++;
	}
	return (exit_status);
}*/

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_unset(t_token **args, char **envp)
{
	int	i;
	int	exit_status;

	(void)envp;
	
	if (!args[1])
	{
		printf("unset: precisa de argumento\n");
		return (1);
	}
	
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]->value))
		{
			printf("unset: '%s': not a valid identifier\n", args[i]->value);
			exit_status = 1;
		}
		else if (unsetenv(args[i]->value) != 0)
		{
			perror("unset");
			exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}
