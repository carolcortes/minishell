/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:49:56 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/26 16:55:06 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
