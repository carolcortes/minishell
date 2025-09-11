/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:50:56 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/11 16:54:31 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Crie um novo arquivo src/pipeline.c
#include "../../inc/minishell.h"

// Função auxiliar: conta quantos argumentos até o próximo pipe
static int count_args_until_pipe(t_token *tokens, int start_index)
{
    int count = 0;
    int i = start_index;
    
    while (tokens[i].value && !tokens[i].is_pipe)
    {
        count++;
        i++;
    }
    return (count);
}

// Função auxiliar: copia tokens para os argumentos do comando
static t_token **copy_command_args(t_token *tokens, int start, int count)
{
    t_token **args;
    int i;
    
    args = malloc(sizeof(t_token *) * (count + 1));
    if (!args)
        return (NULL);
    
    i = 0;
    while (i < count)
    {
        args[i] = &tokens[start + i];
        i++;
    }
    args[count] = NULL;
    
    return (args);
}

t_command *parse_pipeline(t_token *tokens)
{
    t_command *first = NULL;
    t_command *current = NULL;
    t_command *new_cmd;
    int i = 0;
    int arg_count;
    
    if (!tokens || !tokens[0].value)
        return (NULL);
    
    while (tokens[i].value)
    {
        // Pular pipes (eles são separadores, não argumentos)
        if (tokens[i].is_pipe)
        {
            i++;
            continue;
        }
        
        // Contar quantos argumentos até o próximo pipe ou fim
        arg_count = count_args_until_pipe(tokens, i);
        if (arg_count == 0)
            break;
        
        // Criar novo comando
        new_cmd = malloc(sizeof(t_command));
        if (!new_cmd)
            return (free_pipeline(first), NULL);
        
        new_cmd->args = copy_command_args(tokens, i, arg_count);
        new_cmd->argc = arg_count;
        new_cmd->next = NULL;
        new_cmd->prev = current;
        
        // Adicionar à lista
        if (!first)
            first = new_cmd;
        if (current)
            current->next = new_cmd;
        current = new_cmd;
        
        // Avançar o índice
        i += arg_count;
    }
    
    return (first);
}
