/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_ext3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:26:14 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/22 11:29:37 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
