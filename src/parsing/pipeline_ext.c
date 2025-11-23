/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:49:56 by cgross-s          #+#    #+#             */
/*   Updated: 2025/11/23 21:39:10 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	**copy_command_args(t_token *tokens, int start, int count)
{
	t_token	**args;
	int		i;

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

int	count_args_until_pipe(t_token *tokens, int start_index)
{
	int	count;
	int	i;

	count = 0;
	i = start_index;
	while (tokens[i].value && !tokens[i].is_pipe)
	{
		count++;
		i++;
	}
	return (count);
}

int	validate_pipe_count(t_token *tokens, int i, int arg_count)
{
	if (arg_count == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (tokens[i].is_redirection && !tokens[i + 1].value)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	validate_initial_pipe(t_token *tokens)
{
	if (tokens && tokens[0].is_pipe)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	validate_pipe_position(t_token *tokens, int i)
{
	if (!tokens[i].is_pipe)
		return (1);
	if (!tokens[i + 1].value || tokens[i + 1].is_pipe)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
