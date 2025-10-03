/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:48 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/03 13:51:36 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	add_redirection(t_command *cmd, int type, char *filename)
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

//static int	handle_heredoc_redirection(t_command *cmd, char *target)
static int	handle_heredoc_redirection(t_command *cmd, char *target, bool allow_expand, t_shell *shell)
{
	char	*tmpfile;
	//bool	allow_expand; // permição para expandir $

	//tmpfile = handle_heredoc(target);
	//allow_expand = cmd->args[i + 1]->allow_expand;
	//tmpfile = handle_heredoc(target, shell);
	tmpfile = handle_heredoc(target, allow_expand, shell);
	if (!tmpfile)
		return (0);
	add_redirection(cmd, 3, tmpfile);
	free(tmpfile);
	return (1);
}

//static int	process_redirection_token(t_command *cmd, int i)
static int	process_redirection_token(t_command *cmd, int i, t_shell *shell)
{
	int		type;
	char	*target;
	bool	allow_expand;// essa aqui é nova

	if (i + 1 < cmd->argc && cmd->args[i + 1])
	{
		type = cmd->args[i]->redir_type;
		target = cmd->args[i + 1]->value;
		if (cmd->argc == 0 || !cmd->args[0])
		{
			printf("minishell: syntax error near unexpected token `<<'\n");
			return (0);
		}
		if (type == 4)
		{
			allow_expand = cmd->args[i + 1]->allow_expand; // new
			//if (!handle_heredoc_redirection(cmd, target))
			//if (!handle_heredoc_redirection(cmd, target, shell))
			if (!handle_heredoc_redirection(cmd, target, allow_expand, shell))
				return (0);
		}
		else
			add_redirection(cmd, type, target);
		remove_args(cmd, i, 2);
		return (1);
	}
	printf("minishell: syntax error near redirection\n");
	return (0);
}

void	extract_redirections(t_command *cmd, t_shell *shell)
//void	extract_redirections(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (i < cmd->argc && cmd->args[i])
	{
		if (cmd->args[i]->is_redirection)
		{
			//if (!process_redirection_token(cmd, i))
			if (!process_redirection_token(cmd, i, shell))
				break ;
		}
		else
		{
			i++;
		}
	}
}
