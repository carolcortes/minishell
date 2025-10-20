/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:01:53 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/20 21:48:40 by cgross-s         ###   ########.fr       */
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

/*static char    *expand_variables_heredoc(const char *str)
{
    char    *result;
    char    *var_name;
    char    *var_value;
    size_t   i;

    result = ft_strdup("");
    if (!result)
        return (NULL);

    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && (ft_isalpha(str[i+1]) || str[i+1] == '_'))
        {
            // extrai nome da variável
            size_t start = ++i;
            while (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            var_name = ft_substr(str, start, i - start);
            var_value = getenv(var_name); // ou tua função que busca em shell->envp
            if (var_value)
                result = ft_strjoin_free(result, ft_strdup(var_value), 3);
            else
                result = ft_strjoin_free(result, ft_strdup(""), 3);
            free(var_name);
        }
        else
        {
            // copia caractere literal (inclusive " e ')
            char buf[2] = {str[i], '\0'};
            result = ft_strjoin_free(result, ft_strdup(buf), 3);
            i++;
        }
    }
    return result;
}*/


/*static char    *expand_variables_heredoc(const char *str, t_shell *shell)
{
    char    *result = ft_strdup("");
    size_t   i = 0;

	(void)shell;
    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] == '$' && (ft_isalpha(str[i+1]) || str[i+1] == '_'))
        {
            size_t start = ++i;
            while (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            char *var_name = ft_substr(str, start, i - start);
            char *var_value = getenv(var_name); // ou lookup no shell->envp
            if (var_value && *var_value)
                result = ft_strjoin_free(result, ft_strdup(var_value), 3);
            else
            {
                // se a substituição estava entre aspas -> preservar as aspas
                result = ft_strjoin_free(result, ft_strdup(""), 3);
            }
            free(var_name);
        }
        else
        {
            // mantém literais (inclusive " e ')
            char buf[2] = {str[i], '\0'};
            result = ft_strjoin_free(result, ft_strdup(buf), 3);
            i++;
        }
    }
    return result;
}*/


static char *get_env_value(const char *name, t_shell *shell)
{
    int i = 0;
    size_t len = ft_strlen(name);

    while (shell->envp && shell->envp[i])
    {
        if (!ft_strncmp(shell->envp[i], name, len) && shell->envp[i][len] == '=')
            return (shell->envp[i] + len + 1);
        i++;
    }
    return NULL;
}

/*static char *expand_variables_heredoc(const char *str, t_shell *shell)
{
    char *result = ft_strdup("");
    size_t i = 0;

    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] == '$' && (ft_isalpha(str[i+1]) || str[i+1] == '_'))
        {
            size_t start = ++i;
            while (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            char *var_name = ft_substr(str, start, i - start);
            char *var_value = get_env_value(var_name, shell);
			/////////////////////
            if (var_value)
                result = ft_strjoin_free(result, ft_strdup(var_value), 3);
            // se não existir → substitui por string vazia

			if (var_value != NULL)  // mesmo string vazia precisa ser expandida
    			result = ft_strjoin_free(result, ft_strdup(var_value), 3);
			else
    			result = ft_strjoin_free(result, ft_strdup(""), 3);
			///////////////////////
            free(var_name);
        }
        else
        {
            char buf[2] = {str[i], '\0'};
            result = ft_strjoin_free(result, ft_strdup(buf), 3);
            i++;
        }
    }
    return result;
}
*/

static char *expand_variables_heredoc(const char *str, t_shell *shell)
{
    char *result = ft_strdup("");
    size_t i = 0;

    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            // ${VAR}
            if (str[i] == '{')
            {
                size_t start = ++i;
                while (str[i] && str[i] != '}')
                    i++;
                if (str[i] == '}')
                {
                    char *var_name = ft_substr(str, start, i - start);
                    char *var_value = get_env_value(var_name, shell);
                    if (var_value != NULL)
                        result = ft_strjoin_free(result, ft_strdup(var_value), 3);
                    else
                        result = ft_strjoin_free(result, ft_strdup(""), 3);
                    free(var_name);
                    i++; // skip '}'
                }
                else
                {
                    // caso "${VAR" sem fechar
                    result = ft_strjoin_free(result, ft_strdup("${"), 3);
                }
            }
            // $VAR
            else if (ft_isalpha(str[i]) || str[i] == '_')
            {
                size_t start = i;
                while (ft_isalnum(str[i]) || str[i] == '_')
                    i++;
                char *var_name = ft_substr(str, start, i - start);
                char *var_value = get_env_value(var_name, shell);
                if (var_value != NULL)
                    result = ft_strjoin_free(result, ft_strdup(var_value), 3);
                else
                    result = ft_strjoin_free(result, ft_strdup(""), 3);
                free(var_name);
            }
            else
            {
                // caso $ isolado — mantém
                result = ft_strjoin_free(result, ft_strdup("$"), 3);
            }
        }
        else
        {
            char buf[2] = {str[i], '\0'};
            result = ft_strjoin_free(result, ft_strdup(buf), 3);
            i++;
        }
    }
    return result;
}


static void	write_until_delimiter(int fd, char *delimiter,
		bool allow_expand, t_shell *shell)
{
	char	*line;
	char	*expanded;

	//(void)shell;
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
			//expanded = expand_variables(line, shell);
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
