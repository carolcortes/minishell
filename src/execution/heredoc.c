/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:01:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/20 23:02:27 by cade-oli         ###   ########.fr       */
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

char	*get_env_var_value(const char *name, t_shell *shell)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->envp && shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], name, len)
			&& shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*static char	*expand_braced_var(const char *str, size_t *i, t_shell *sh)
{
	char	*name;
	char	*val;
	size_t	start;
	char	*res;

	res = ft_strdup("");
	start = ++(*i);
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] == '}')
	{
		name = ft_substr(str, start, *i - start);
		val = get_env_value(name, sh);
		res = ft_strjoin_free(res, ft_strdup(val ? val : ""), 3);
		free(name);
		(*i)++;
	}
	else
		res = ft_strjoin_free(res, ft_strdup("${"), 3);
	return (res);
}

static char	*expand_simple_var(const char *str, size_t *i, t_shell *sh)
{
	size_t	start;
	char	*name;
	char	*val;
	char	*res;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	name = ft_substr(str, start, *i - start);
	val = get_env_value(name, sh);
	res = ft_strdup(val ? val : "");
	free(name);
	return (res);
}

static char	*expand_variables_heredoc(const char *s, t_shell *sh)
{
	char	*r;
	size_t	i;
	char	buf[2];

	r = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '{')
				r = ft_strjoin_free(r, expand_braced_var(s, &i, sh), 3);
			else if (ft_isalpha(s[i]) || s[i] == '_')
				r = ft_strjoin_free(r, expand_simple_var(s, &i, sh), 3);
			else
				r = ft_strjoin_free(r, ft_strdup("$"), 3);
		}
		else
		{
			buf[0] = s[i++];
			buf[1] = '\0';
			r = ft_strjoin_free(r, ft_strdup(buf), 3);
		}
	}
	return (r);
}*/
/*static void	append_char(char **res, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strdup(buf);
	*res = ft_strjoin_free(*res, tmp, 3);
}*/

char	*expand_variables_heredoc(const char *s, t_shell *shell)
{
	char	*res;
	size_t	i;

	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '{')
				res = ft_strjoin_free(res,
						expand_braced_var(s, &i, shell), 3);
			else if (ft_isalpha(s[i]) || s[i] == '_')
				res = ft_strjoin_free(res,
						expand_simple_var(s, &i, shell), 3);
			else
				append_char(&res, '$');
		}
		else
			append_char(&res, s[i++]);
	}
	return (res);
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
			expanded = expand_variables_heredoc(line, shell);
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
