/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:31:44 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/22 15:31:33 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static void	add_redirection(t_command *cmd, int type, char *filename)
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

void	extract_redirections(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (i < cmd->argc && cmd->args[i])
	{
		if (cmd->args[i]->is_redirection)
		{
			if (i + 1 < cmd->argc && cmd->args[i + 1])
			{
				add_redirection(cmd, cmd->args[i]->redir_type,
					cmd->args[i + 1]->value);
				remove_args(cmd, i, 2);
			}
			else
			{
				printf("minishell: syntax error near redirection\n");
				break ;
			}
		}
		else
		{
			i++;
		}
	}
}*/

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

/*void	extract_redirections(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (i < cmd->argc && cmd->args[i])
	{
		if (cmd->args[i]->is_redirection)
		{
			if (i + 1 < cmd->argc && cmd->args[i + 1])
			{
				add_redirection(cmd, cmd->args[i]->redir_type,
					cmd->args[i + 1]->value);
				remove_args(cmd, i, 2);
			}
			else
			{
				printf("minishell: syntax error near redirection\n");
				break ;
			}
		}
		else
		{
			i++;
		}
	}
}*/

void	extract_redirections(t_command *cmd)
{
	int	i;

	//printf("=== DEBUG EXTRACT_REDIRECTIONS START ===\n");
	//printf("Command has %d args\n", cmd->argc);
	
	if (!cmd || !cmd->args)
	{
		//printf("DEBUG: No command or args\n");
		return;
	}
	
	i = 0;
	while (i < cmd->argc && cmd->args[i])
	{
		/*printf("Arg %d: '%s' (redir: %d, type: %d)\n", 
			i, cmd->args[i]->value, 
			cmd->args[i]->is_redirection, cmd->args[i]->redir_type);*/
		
		if (cmd->args[i]->is_redirection)
		{
			/*printf("DEBUG: Found redirection '%s' at position %d\n", 
				cmd->args[i]->value, i);*/
			
			if (i + 1 < cmd->argc && cmd->args[i + 1])
			{
				/*printf("DEBUG: Adding redirection type %d with filename '%s'\n",
					cmd->args[i]->redir_type, cmd->args[i + 1]->value);*/
				add_redirection(cmd, cmd->args[i]->redir_type,
					cmd->args[i + 1]->value);
				remove_args(cmd, i, 2);
			}
			else
			{
				printf("minishell: syntax error near redirection\n");
				//printf("DEBUG: Syntax error - no filename after redirection\n");
				break;
			}
		}
		else
		{
			i++;
		}
	}
	/*printf("DEBUG: After extraction - %d args, %d redirections\n", 
		cmd->argc, cmd->redir_count);
	printf("=== DEBUG EXTRACT_REDIRECTIONS END ===\n");*/
}
