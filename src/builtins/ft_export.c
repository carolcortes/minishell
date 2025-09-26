/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:12 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/26 10:32:22 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
