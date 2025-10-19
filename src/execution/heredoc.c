/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:01:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 23:27:52 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_tmpfile(int *fd);
static void	write_until_delimiter(int fd, char *delimiter,
				bool allow_expand, t_shell *shell);

/**
 * @brief Handle a here-document.
 *
 * Reads lines until the delimiter, optionally expands variables, writes
 * them to a temporary file, and returns its path.
 *
 * @param delimiter End marker string.
 * @param allow_expand Whether to expand variables in lines.
 * @param shell Shell state used for variable expansion.
 * @return Allocated path to the temp file, or NULL on error.
 */

char	*handle_heredoc(char *delimiter, bool allow_expand, t_shell *shell)
{
	char	*filename;
	int		fd;

	filename = create_tmpfile(&fd);
	if (!filename)
		return (NULL);
	write_until_delimiter(fd, delimiter, allow_expand, shell);
	close(fd);
	return (filename);
}

static char	*create_tmpfile(int *fd)
{
	static int	index = 0;
	char		tmpname[64];
	char		*filename;

	snprintf(tmpname, sizeof(tmpname),
		"/tmp/minishell_heredoc_%d", index++);
	filename = ft_strdup(tmpname);
	if (!filename)
		return (NULL);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd < 0)
	{
		perror("minishell");
		free(filename);
		return (NULL);
	}
	return (filename);
}

static void	write_until_delimiter(int fd, char *delimiter,
		bool allow_expand, t_shell *shell)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (allow_expand)
		{
			expanded = expand_variables(line, shell);
			if (expanded)
			{
				write(fd, expanded, ft_strlen(expanded));
				free(expanded);
			}
		}
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
