/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:18:42 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 20:29:36 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	apply_heredoc(t_redirection *redir);
static int	apply_output_redirection(t_redirection *redir);
static int	apply_input_redirection(t_redirection *redir);
static int	process_single_redirection(t_redirection *redir);

/**
 * @brief Apply I/O redirections for a command.
 *
 * Processes each redirection in cmd->redirs: >, >>, < and << (heredoc);
 * opens the files/pipes and dup2s them onto STDIN/STDOUT.
 *
 * @param cmd Command containing the redirection array and count.
 * @return 1 on success; 0 on error.
 */

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

static int	apply_heredoc(t_redirection *redir)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (0);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->filename) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (0);
	}
	close(pipefd[0]);
	return (1);
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
	else if (redir->type == 4)
		return (apply_heredoc(redir));
	return (1);
}
