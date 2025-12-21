/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:04:21 by cgross-s          #+#    #+#             */
/*   Updated: 2025/12/21 19:08:37 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_token(t_token *token, char *value)
{
	token->value = value;
	token->quoted = false;
	token->allow_expand = false;
	token->is_pipe = false;
	token->is_redirection = false;
	token->redir_type = 0;
}

void	insert_split_tokens(t_token *tokens, int index, char **words)
{
	int	i;
	int	k;

	if (!words || !words[0])
		return ;
	free(tokens[index].value);
	init_token(&tokens[index], words[0]);
	i = index + 1;
	k = 1;
	while (words[k])
	{
		while (tokens[i].value)
			i++;
		init_token(&tokens[i], words[k]);
		tokens[i + 1].value = NULL;
		k++;
	}
}
