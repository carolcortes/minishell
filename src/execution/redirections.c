/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:18:42 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/22 15:37:33 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static int open_output_file(char *filename, int append)
{
    int flags;
    int fd;

    if (append)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    
    fd = open(filename, flags, 0644);
    if (fd == -1)
    {
        perror("minishell");
        return (-1);
    }
    return (fd);
}

static int open_input_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("minishell");
        return (-1);
    }
    return (fd);
}

int apply_redirections(t_command *cmd)
{
    int i;
    int fd;

    i = 0;
    while (i < cmd->redir_count)
    {
        if (cmd->redirs[i].type == 1 || cmd->redirs[i].type == 2) // > ou >>
        {
            fd = open_output_file(cmd->redirs[i].filename, 
                 cmd->redirs[i].type == 2);
            if (fd == -1)
                return (0);
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("minishell");
                close(fd);
                return (0);
            }
            close(fd);
        }
        else if (cmd->redirs[i].type == 3) // <
        {
            fd = open_input_file(cmd->redirs[i].filename);
            if (fd == -1)
                return (0);
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                perror("minishell");
                close(fd);
                return (0);
            }
            close(fd);
        }
        i++;
    }
    return (1);
}

////

static void	add_redirection(t_command *cmd, int type, char *filename)
{
    t_redirection	*new_redirs;
    int				new_count;

    new_count = cmd->redir_count + 1;
    new_redirs = realloc(cmd->redirs, sizeof(t_redirection) * new_count);
    if (!new_redirs)
        return;
    
    cmd->redirs = new_redirs;
    cmd->redirs[cmd->redir_count].type = type;
    cmd->redirs[cmd->redir_count].filename = ft_strdup(filename);
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

    i = 0;
    while (i < cmd->argc && cmd->args[i])
    {
        if (cmd->args[i]->is_redirection && cmd->args[i + 1])
        {
            add_redirection(cmd, cmd->args[i]->redir_type, 
                          cmd->args[i + 1]->value);
            remove_args(cmd, i, 2); // Remove redirecionamento + filename
        }
        else
        {
            i++;
        }
    }
}*/

static int	open_output_file(char *filename, int append)
{
	int	flags;
	int	fd;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}

static int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}

int	apply_redirections(t_command *cmd)
{
	int	i;
	int	fd;

	//printf("=== DEBUG APPLY_REDIRECTIONS START ===\n");
	//printf("Command has %d redirections\n", cmd->redir_count);

	if (!cmd || !cmd->redirs)
	{
		//printf("DEBUG: No redirections to apply\n");
		return (1);
	}
	
	i = 0;
	while (i < cmd->redir_count)
	{
		/*printf("DEBUG: Applying redirection %d: type=%d, file='%s'\n",
			i, cmd->redirs[i].type, cmd->redirs[i].filename);*/
		if (cmd->redirs[i].type == 1 || cmd->redirs[i].type == 2)
		{
			fd = open_output_file(cmd->redirs[i].filename,
					cmd->redirs[i].type == 2);
			if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
			{
				if (fd != -1)
					close(fd);
				return (0);
			}
			close(fd);
		}
		else if (cmd->redirs[i].type == 3)
		{
			fd = open_input_file(cmd->redirs[i].filename);
			if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			{
				if (fd != -1)
					close(fd);
				return (0);
			}
			close(fd);
		}
		i++;
	}
	//printf("=== DEBUG APPLY_REDIRECTIONS END ===\n");
	return (1);
}
