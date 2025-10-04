/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:49:56 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/01 11:47:34 by cgross-s         ###   ########.fr       */
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
