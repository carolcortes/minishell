/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:12 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/25 22:02:33 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

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

//int	ft_export(t_token **args)
/*int	ft_export(t_token **args, char **envp)
{
	(void)envp; // ✅ Marcar como não usado
	if (!args[1])
	{
		printf("export: precisa de argumento\n");
		return (1);
	}
	if (putenv(args[1]->value) != 0)
	{
		perror("export");
		return (1);
	}
	return (0);
}*/

/*static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	print_exported_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

static int	export_variable(char *var, char ***envp)
{
	int		i;
	char	*equal_sign;
	char	*key;

	if (!is_valid_identifier(var))
	{
		printf("export: '%s': not a valid identifier\n", var);
		return (1);
	}
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		key = ft_substr(var, 0, equal_sign - var);
		i = 0;
		while ((*envp)[i])
		{
			if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0
				&& (*envp)[i][ft_strlen(key)] == '=')
			{
				free((*envp)[i]);
				(*envp)[i] = ft_strdup(var);
				free(key);
				return (0);
			}
			i++;
		}
		free(key);
	}
	return (add_variable_to_env(var, envp));
}

int	ft_export(t_token **args, char ***envp)
{
	int	i;
	int	exit_status;

	if (!args[1])
	{
		print_exported_vars(*envp);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (export_variable(args[i]->value, envp) != 0)
			exit_status = 1;
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
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	print_exported_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

static int	add_variable_to_env(char *var, char **envp)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < count)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	return (0);
}

static int	export_variable(char *var, char **envp)
{
	int		i;
	char	*equal_sign;
	char	*key;

	if (!is_valid_identifier(var))
	{
		printf("export: '%s': not a valid identifier\n", var);
		return (1);
	}
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		key = ft_substr(var, 0, equal_sign - var);
		i = 0;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
				&& envp[i][ft_strlen(key)] == '=')
			{
				free(envp[i]);
				envp[i] = ft_strdup(var);
				free(key);
				return (0);
			}
			i++;
		}
		free(key);
	}
	return (add_variable_to_env(var, envp));
}

int	ft_export(t_token **args, char **envp)
{
	int	i;
	int	exit_status;

	if (!args[1])
	{
		print_exported_vars(envp);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (export_variable(args[i]->value, envp) != 0)
			exit_status = 1;
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
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_export(t_token **args, char **envp)
{
	char	*var_copy;

	(void)envp;
	
	if (!args[1])
	{
		printf("export: precisa de argumento\n");
		return (1);
	}
	
	if (!is_valid_identifier(args[1]->value))
	{
		printf("export: '%s': not a valid identifier\n", args[1]->value);
		return (1);
	}
	
	// Duplicar a string para putenv (ela não pode ser liberada)
	var_copy = ft_strdup(args[1]->value);
	if (!var_copy)
	{
		perror("export");
		return (1);
	}
	
	if (putenv(var_copy) != 0)
	{
		perror("export");
		free(var_copy);
		return (1);
	}
	
	// Não liberar var_copy - putenv assume posse da string
	return (0);
}*/


/*static int add_or_update_env(char *var, char ***envp)
{
    int     i;
    char    *equal_sign;
    char    *key;

    equal_sign = ft_strchr(var, '=');
    if (!equal_sign)
        return (0); // só exporta, sem valor (tipo "export VAR")

    key = ft_substr(var, 0, equal_sign - var);
    if (!key)
        return (1);

    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0
            && (*envp)[i][ft_strlen(key)] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = ft_strdup(var);
            free(key);
            return (0);
        }
        i++;
    }

    // não existe ainda → adiciona
    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        free(key);
        return (1);
    }
    for (int j = 0; j < i; j++)
        new_env[j] = (*envp)[j];
    new_env[i] = ft_strdup(var);
    new_env[i + 1] = NULL;

    free(*envp);
    *envp = new_env;
    free(key);
    return (0);
}

int ft_export(t_token **args, char ***envp)
{
    int i = 1;
    int status = 0;

    if (!args[1])
    {
        // print vars com formato declare -x
        for (int j = 0; (*envp)[j]; j++)
            printf("declare -x %s\n", (*envp)[j]);
        return 0;
    }
    while (args[i])
    {
        if (!is_valid_identifier(args[i]->value))
        {
            printf("export: '%s': not a valid identifier\n", args[i]->value);
            status = 1;
        }
        else if (add_or_update_env(args[i]->value, envp))
            status = 1;
        i++;
    }
    return status;
}*/

/*#include "../inc/minishell.h"

static bool is_valid_identifier(char *str)
{
    int i;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (false);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

static int add_or_update_env(char *var, char ***envp)
{
    int     i;
    char    *equal_sign;
    char    *key;

    equal_sign = ft_strchr(var, '=');
    if (!equal_sign)
        return (0); // só exporta, sem valor (tipo "export VAR")

    key = ft_substr(var, 0, equal_sign - var);
    if (!key)
        return (1);

    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0
            && (*envp)[i][ft_strlen(key)] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = ft_strdup(var);
            free(key);
            return (0);
        }
        i++;
    }

    // não existe ainda → adiciona
    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        free(key);
        return (1);
    }
    for (int j = 0; j < i; j++)
        new_env[j] = (*envp)[j];
    new_env[i] = ft_strdup(var);
    new_env[i + 1] = NULL;

    free(*envp);
    *envp = new_env;
    free(key);
    return (0);
}

int ft_export(t_token **args, char ***envp)
{
    int i = 1;
    int status = 0;

    if (!args[1])
    {
        // print vars com formato declare -x
        for (int j = 0; (*envp)[j]; j++)
            printf("declare -x %s\n", (*envp)[j]);
        return 0;
    }
    while (args[i])
    {
        if (!is_valid_identifier(args[i]->value))
        {
            printf("export: '%s': not a valid identifier\n", args[i]->value);
            status = 1;
        }
        else if (add_or_update_env(args[i]->value, envp))
            status = 1;
        i++;
    }
    return status;
}*/

#include "../inc/minishell.h"

static bool is_valid_identifier(char *str)
{
    int i;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (false);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

static int add_or_update_env(char *var, char **envp)
{
    int     i;
    char    *equal_sign;
    char    *key;

    equal_sign = ft_strchr(var, '=');
    if (!equal_sign)
        return (0); // só exporta, sem valor

    key = ft_substr(var, 0, equal_sign - var);
    if (!key)
        return (1);

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
            && envp[i][ft_strlen(key)] == '=')
        {
            free(envp[i]);
            envp[i] = ft_strdup(var);
            free(key);
            return (0);
        }
        i++;
    }

    // se não encontrou, insere no final
    envp[i] = ft_strdup(var);
    envp[i + 1] = NULL;
    free(key);
    return (0);
}

int ft_export(t_token **args, char **envp)
{
    int i = 1;
    int status = 0;

    if (!args[1])
    {
        for (int j = 0; envp[j]; j++)
            printf("declare -x %s\n", envp[j]);
        return 0;
    }
    while (args[i])
    {
        if (!is_valid_identifier(args[i]->value))
        {
            printf("export: '%s': not a valid identifier\n", args[i]->value);
            status = 1;
        }
        else if (add_or_update_env(args[i]->value, envp))
            status = 1;
        i++;
    }
    return status;
}
