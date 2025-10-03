/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:01:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/03 11:21:53 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	write_until_delimiter(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

//char	*handle_heredoc(char *delimiter)
char	*handle_heredoc(char *delimiter, t_shell *shell)
{
	char	*filename;
	int		fd;
	(void)shell; // por hora

	filename = create_tmpfile(&fd);
	if (!filename)
		return (NULL);
	write_until_delimiter(fd, delimiter);
	close(fd);
	return (filename);
}
