/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:18:42 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/25 09:08:05 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../inc/minishell.h"

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

	if (!cmd || !cmd->redirs)
		return (1);
	i = 0;
	while (i < cmd->redir_count)
	{
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
	return (1);
}*/

#include "../../inc/minishell.h"

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

static int	apply_output_redirection(t_redirection *redir)
{
	int	fd;

	fd = open_output_file(redir->filename, redir->type == 2);
	if (fd == -1)
		return (0);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	apply_input_redirection(t_redirection *redir)
{
	int	fd;

	fd = open_input_file(redir->filename);
	if (fd == -1)
		return (0);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	process_single_redirection(t_redirection *redir)
{
	if (redir->type == 1 || redir->type == 2)
		return (apply_output_redirection(redir));
	else if (redir->type == 3)
		return (apply_input_redirection(redir));
	return (1);
}

int	apply_redirections(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->redirs)
		return (1);
	i = 0;
	while (i < cmd->redir_count)
	{
		if (!process_single_redirection(&cmd->redirs[i]))
			return (0);
		i++;
	}
	return (1);
}
