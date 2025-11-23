/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:48 by cgross-s          #+#    #+#             */
/*   Updated: 2025/11/23 21:27:38 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (!cmd->args[i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

static int	process_hd(t_command *cmd, int i, t_shell *shell)
{
	char	*expanded;
	int		ok;
	bool	allow_expand;

	allow_expand = !cmd->args[i + 1]->quoted;
	expanded = ft_strdup(cmd->args[i + 1]->value);
	if (!expanded)
		return (0);
	ok = handle_heredoc_redirection(cmd, expanded, allow_expand, shell);
	free(expanded);
	return (ok);
}

static int	process_redirection_token(t_command *cmd, int i, t_shell *shell)
{
	int		type;
	char	*target;

	if (!validate_redirection_syntax(cmd, i))
		return (0);
	type = cmd->args[i]->redir_type;
	target = cmd->args[i + 1]->value;
	if (type == 4)
	{
		if (!process_hd(cmd, i, shell))
			return (0);
	}
	else
		add_redirection(cmd, type, target);
	remove_args(cmd, i, 2);
	return (1);
}

int	extract_redirections(t_command *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->args)
		return (1);
	i = 0;
	while (i < cmd->argc && cmd->args[i])
	{
		if (cmd->args[i]->is_redirection)
		{
			if (!process_redirection_token(cmd, i, shell))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
