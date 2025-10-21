/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:48 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/21 22:45:43 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	remove_args(t_command *cmd, int start, int count)
{
	int	i;

	i = start;
	while (i + count < cmd->argc)
	{
		cmd->args[i] = cmd->args[i + count];
		i++;
	}
	cmd->argc -= count;
	cmd->args[cmd->argc] = NULL;
}

static int	handle_heredoc_redirection(t_command *cmd,
		char *target, bool allow_expand, t_shell *shell)
{
	char	*tmpfile;

	tmpfile = handle_heredoc(target, allow_expand, shell);
	if (!tmpfile)
		return (0);
	add_redirection(cmd, 3, tmpfile);
	free(tmpfile);
	return (1);
}

static int	validate_redirection_syntax(t_command *cmd, int i)
{
	if (cmd->argc == 0 || !cmd->args[0])
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (0);
	}
	if (!cmd->args[i + 1])
	{
		printf("minishell: syntax error near redirection\n");
		return (0);
	}
	return (1);
}

static int	process_redirection_token(t_command *cmd, int i, t_shell *shell)
{
	int		type;
	char	*target;
	bool	allow_expand;

	if (!validate_redirection_syntax(cmd, i))
		return (0);
	type = cmd->args[i]->redir_type;
	target = cmd->args[i + 1]->value;
	if (type == 4)
	{
		if (cmd->args[i + 1]->quoted)
			allow_expand = false;
		else
			allow_expand = true;
		if (!handle_heredoc_redirection(cmd, target, allow_expand, shell))
			return (0);
	}
	else
		add_redirection(cmd, type, target);
	remove_args(cmd, i, 2);
	return (1);
}

void	extract_redirections(t_command *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (i < cmd->argc && cmd->args[i])
	{
		if (cmd->args[i]->is_redirection)
		{
			if (!process_redirection_token(cmd, i, shell))
				break ;
		}
		else
			i++;
	}
}
