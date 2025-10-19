/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:18:42 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 19:43:17 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//static int	apply_heredoc(t_redirection *redir);
//static int	apply_heredoc(t_redirection *redir, t_shell *shell, bool allow_expand);
static int	apply_output_redirection(t_redirection *redir);
static int	apply_input_redirection(t_redirection *redir);
//static int	process_single_redirection(t_redirection *redir);
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

//int	apply_redirections(t_command *cmd)
int	apply_redirections(t_command *cmd, t_shell *shell, t_token *tokens)
{
	int	i;

	if (!cmd || !cmd->redirs)
		return (1);
	i = 0;
	while (i < cmd->redir_count)
	{
		//if (!process_single_redirection(&cmd->redirs[i]))
		if (!process_single_redirection(&cmd->redirs[i], shell, tokens))
			return (0);
		i++;
	}
	return (1);
}

/*static int	apply_heredoc(t_redirection *redir, t_shell *shell, bool allow_expand)
{
	int		pipefd[2];
	char	*line;

	(void)shell;
	(void)allow_expand;
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
}*/

/*static int	apply_heredoc(t_redirection *redir, t_shell *shell, bool allow_expand)
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
		if (allow_expand)
		{
			char *expanded = expand_variables(line, shell);
			free(line);
			line = expanded;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (1);
}*/


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

/*//static int	process_single_redirection(t_redirection *redir)
static int	process_single_redirection(t_redirection *redir,
	t_shell *shell, t_token *tokens)
{
	if (redir->type == 1 || redir->type == 2)
		return (apply_output_redirection(redir));
	else if (redir->type == 3)
		return (apply_input_redirection(redir));
	else if (redir->type == 4)
		//return (apply_heredoc(redir));
		//return (apply_heredoc(redir, shell, tokens));
		return (apply_heredoc(redir, shell, tokens->allow_expand));
	return (1);
}*/

static int	process_single_redirection(t_redirection *redir,
	t_shell *shell, t_token *tokens)
{
	(void)tokens;
	(void)shell;
    if (redir->type == 1 || redir->type == 2)
        return (apply_output_redirection(redir));
//    else if (redir->type == 3 || redir->type == 4)
//        return (apply_input_redirection(redir)); // << já foi transformado em <
	else if (redir->type == 3)
        return (apply_input_redirection(redir));
	return (1);
}
