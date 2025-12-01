/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:18:42 by cgross-s          #+#    #+#             */
/*   Updated: 2025/11/25 21:47:23 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	apply_output_redirection(t_redirection *redir);
static int	apply_input_redirection(t_redirection *redir);
static int	process_single_redirection(t_redirection *redir,
				t_shell *shell, t_token *tokens);

/**
 * @brief Apply I/O redirections for a command.
 *
 * Processes each redirection in cmd->redirs: >, >>, < and << (heredoc);
 * opens the files/pipes and dup2s them onto STDIN/STDOUT.
 *
 * @param cmd Command containing the redirection array and count.
 * @return 1 on success; 0 on error.
 */

int	apply_redirections(t_command *cmd, t_shell *shell, t_token *tokens)
{
	int	i;

	if (!cmd || !cmd->redirs)
		return (1);
	i = 0;
	while (i < cmd->redir_count)
	{
		if (!process_single_redirection(&cmd->redirs[i], shell, tokens))
			return (0);
		i++;
	}
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

static int	process_single_redirection(t_redirection *redir,
	t_shell *shell, t_token *tokens)
{
	int	fd;

	(void)tokens;
	(void)shell;
	if (redir->type == 1 || redir->type == 2)
		return (apply_output_redirection(redir));
	else if (redir->type == 3)
		return (apply_input_redirection(redir));
	else if (redir->type == 4)
	{
		fd = open(redir->filename, O_RDONLY);
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
	return (1);
}
