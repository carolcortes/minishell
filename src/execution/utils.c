/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:18:08 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 18:59:19 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../inc/minishell.h"

// Verifica se é um builtin
bool is_builtin(t_token **args)
{
    if (!args || !args[0])
        return (false);
    
    // Lista de builtins (atualize conforme necessário)
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    
    for (int i = 0; builtins[i]; i++)
    {
        if (ft_strcmp(args[0]->value, builtins[i]) == 0)
            return (true);
    }
    return (false);
}

// Converte t_token** para char**
char **tokens_to_argv(t_token **tokens)
{
    int count = 0;
    char **argv;
    
    while (tokens[count])
        count++;
    
    argv = malloc(sizeof(char *) * (count + 1));
    for (int i = 0; i < count; i++)
    {
        argv[i] = ft_strdup(tokens[i]->value);
    }
    argv[count] = NULL;
    
    return (argv);
}

// Libera array de strings
void free_argv(char **argv)
{
    int i = 0;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}
*/

#include "../../inc/minishell.h"

// Verifica se é um builtin
bool is_builtin(t_token **args)
{
    if (!args || !args[0])
        return (false);
    
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    
    for (int i = 0; builtins[i]; i++)
    {
        if (ft_strcmp(args[0]->value, builtins[i]) == 0)
            return (true);
    }
    return (false);
}

// Converte t_token** para char**
char **tokens_to_argv(t_token **tokens)
{
    int count = 0;
    char **argv;
    
    if (!tokens)
        return (NULL);
    
    while (tokens[count])
        count++;
    
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
    
    for (int i = 0; i < count; i++)
    {
        argv[i] = ft_strdup(tokens[i]->value);
        if (!argv[i])
        {
            free_argv(argv);
            return (NULL);
        }
    }
    argv[count] = NULL;
    
    return (argv);
}

// Libera array de strings
void free_argv(char **argv)
{
    int i = 0;
    
    if (!argv)
        return;
    
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}
