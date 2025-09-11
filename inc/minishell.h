/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/11 17:40:59 by cgross-s         ###   ########.fr       */
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
# define MAG	"\033[1;95m"
# define RST 	"\033[0m"

# define WHITESPACES "\t\n\v\f\r "

// Struct para tokens
// Na struct s_token, adicione:
typedef struct s_token
{
    char	*value;
    bool	allow_expand;
    bool	is_pipe;        // NOVO
    bool	is_redirection; // NOVO (para futuro)
}	t_token;

typedef struct s_builtin
{
	const char	*builtin_name;
	int			(*builtin)(t_token **av);
}	t_builtin;


// Adicione estas estruturas no minishell.h
typedef struct s_command {
    t_token      **args;     // Array de tokens deste comando
    int          argc;       // Número de argumentos
    struct s_command *next;  // Próximo comando na pipeline
    struct s_command *prev;  // Comando anterior (opcional)
} t_command;

// Protótipo da nova função
t_command *parse_pipeline(t_token *tokens);
void       free_pipeline(t_command *pipeline);

// Funções de parsing e tokens
// main.c
char	*shell_read_line(void);

// tokens.c
t_token	*shell_split_line_quotes(char *line);

// expand.c
void	expand_tokens(t_token *tokens, int last_status);

// signals
void	setup_signals(void);

// builtins
int		exec_builtin(t_token **args, char **envp);
int		ft_exit(t_token **args);
int		ft_echo(t_token **args);
int		ft_cd(t_token **args);
int		ft_pwd(t_token **args);
int		ft_env(t_token **args, char **envp);
int		ft_export(t_token **args);
int		ft_unset(t_token **args);

char	**dup_env(char **envp);
void	free_env(char **env);

// utils.c
void	ft_getcwd(char *buf, size_t size);
void	printbanner(void);
bool	is_spaces(char c);

// free.c
void	free_array(char **arr);
void	free_tokens(t_token *tokens);
char	*ft_strjoin_free(char *s1, char *s2, int mode);

// execution functions
void    execute_pipeline(t_command *pipeline, char **envp);
void    execute_external(t_token **args, char **envp);
bool    is_builtin(t_token **args);
char    **tokens_to_argv(t_token **tokens);
void    free_argv(char **argv);

// path finding (necessária para execute_external)
char    *find_command_path(char *command, char **envp);

#endif
