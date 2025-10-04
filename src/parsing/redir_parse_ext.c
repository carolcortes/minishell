/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:10:24 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/03 15:14:57 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_redirection(t_command *cmd, int type, char *filename)
{
	t_redirection	*new_redirs;
	int				new_count;

	new_count = cmd->redir_count + 1;
	new_redirs = realloc(cmd->redirs, sizeof(t_redirection) * new_count);
	if (!new_redirs)
		return ;
	cmd->redirs = new_redirs;
	cmd->redirs[cmd->redir_count].type = type;
	cmd->redirs[cmd->redir_count].filename = ft_strdup(filename);
	if (!cmd->redirs[cmd->redir_count].filename)
		return ;
	cmd->redir_count = new_count;
}
