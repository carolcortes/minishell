/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:26:14 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/26 16:32:40 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

t_token	create_pipe_token(void)
{
	t_token	pipe_token;

	pipe_token.value = ft_strdup("|");
	pipe_token.allow_expand = false;
	pipe_token.is_pipe = true;
	pipe_token.is_redirection = false;
	pipe_token.redir_type = 0;
	return (pipe_token);
}

t_token	create_redirection_token(char *value, int type)
{
	t_token	token;

	token.value = ft_strdup(value);
	token.allow_expand = true;
	token.is_pipe = false;
	token.is_redirection = true;
	token.redir_type = type;
	return (token);
}
