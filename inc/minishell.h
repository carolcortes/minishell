/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/21 22:34:54 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sysexits.h>

# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

// ANSI Color codes
# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED	"\033[1;31m"
# define RST 	"\033[0m"

# define WHITESPACES "\t\n\v\f\r "

// Struct para tokens
typedef struct s_token
{
    char    *value;
    bool    allow_expand;
}   t_token;

typedef struct s_builtin
{
    const char  *builtin_name;
    int         (*foo)(char **av);
}   t_builtin;

// Protótipos das funções
void    ft_getcwd(char *buf, size_t size);
void    printbanner(void);
int     shell_exit(char **args);
void    setup_signals(void);

// Funções de parsing e tokens
char    *ft_strjoin_free(char *s1, char *s2, int mode);
char    *expand_variables(const char *str, int last_status);
char    *shell_read_line(void);
t_token *shell_split_line_quotes(char *line);
void    expand_tokens(t_token *tokens, int last_status);
void    free_tokens(t_token *tokens);

// Funções auxiliares
char    *handle_env_var(const char *str, int *i, char *result);
char    *handle_literal_char(const char *str, int *i, char *result);
bool    process_token(char *line, int *i, t_token **tokens, int *count, int *capacity);
bool    process_quoted_part(char *line, int *i, char **token, bool *allow_expand);
bool    process_regular_char(char *line, int *i, char **token);
char    *extract_quoted(const char *line, int *i, bool *allow_expand);
bool    is_spaces(char c);
char	*ft_strjoin_free(char *s1, char *s2, int mode);

#endif