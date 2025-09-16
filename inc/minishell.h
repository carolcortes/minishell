/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/16 17:37:39 by cgross-s         ###   ########.fr       */
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

extern int	g_last_status;	// ✅ EXTERN - apenas declaração

// ANSI Color codes
# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED	"\033[1;31m"
# define MAG	"\033[1;95m"
# define RST 	"\033[0m"

# define WHITESPACES "\t\n\v\f\r "

// Struct para tokens
typedef struct s_token
{
	char	*value;
	bool	allow_expand;
	bool	is_pipe;		// NOVO
	bool	is_redirection; // NOVO (para futuro)
}	t_token;

typedef struct s_builtin
{
	const char	*builtin_name;
	int			(*builtin)(t_token **av);
}	t_builtin;

typedef struct s_command
{
	t_token				**args;		// Array de tokens deste comando
	int					argc;		// Número de argumentos
	struct s_command	*next;		// Próximo comando na pipeline
	struct s_command	*prev;		// Comando anterior (opcional)
}	t_command;

typedef struct s_exec_data
{
	int			*input_fd;
	int			pipe_fd[2];
	pid_t		*last_pid;
	char		**envp;
}	t_exec_data;

typedef struct s_fork_data
{
	int			input_fd;
	int			pipe_fd[2];
	pid_t		*last_pid;
	char		**envp;
}	t_fork_data;

typedef struct s_token_data
{
	t_token	*tokens;	// ✅ Ponteiro para array
	int		count;		// ✅ Inteiro (não ponteiro)
	int		capacity;	// ✅ Inteiro (não ponteiro)
}	t_token_data;

typedef struct s_quote_data
{
	char	**token;
	bool	*allow_expand;
}	t_quote_data;

// builtins
int			exec_builtin(t_token **args, char **envp);
int			ft_cd(t_token **args);
int			ft_echo(t_token **args);
int			ft_env(t_token **args, char **envp);
char		**dup_env(char **envp);
void		free_env(char **env);
int			ft_exit(t_token **args);
int			ft_export(t_token **args);
int			ft_pwd(t_token **args);
int			ft_unset(t_token **args);

//	execution
//		execute_pipeline_ext.c
void		redirect_input(int input_fd);
void		redirect_output(int pipe_fd[2]);
void		execute_command(t_command *cmd, char **envp);
void		handle_child_process(t_command *cmd, int input_fd,
				int pipe_fd[2], char **envp);
void		update_fds_after_command(t_command *cmd, t_exec_data *data);
//		execute_pipeline.c
void		execute_pipeline(t_command *pipeline, char **envp);
//		external.c
int			execute_external(t_token **args, char **envp);
//		path.c
char		*find_command_path(char *command, char **envp);
//		utils.c
bool		is_builtin(t_token **args);
char		**tokens_to_argv(t_token **tokens);
void		free_argv(char **argv);

//	parsing
//		parse_pipeline.c
t_command	*parse_pipeline(t_token *tokens);
//		tokens.c
t_token		*shell_split_line_quotes(char *line);
//		tokens_ext1.c
bool		is_special_char(char c);
t_token		create_pipe_token(void);
bool		expand_token_array(t_token_data *data);
bool		process_special_char(char *line, int *i, t_token_data *data);
char		*extract_quoted(const char *line, int *i, bool *allow_expand);
//		tokens_ext2.c
bool		process_quoted_part(char *line, int *i, t_quote_data *qdata);
bool		process_regular_char(char *line, int *i, char **token);
bool		process_word_chars(char *line, int *i,
				t_quote_data *qdata);
bool		add_token_to_array(t_token_data *data, char *token,
				bool allow_expand);
bool		process_word_token(char *line, int *i, t_token_data *data);

// expand.c
void		expand_tokens(t_token *tokens, int last_status);

// free.c
void		free_array(char **arr);
void		free_tokens(t_token *tokens);
char		*ft_strjoin_free(char *s1, char *s2, int mode);
void		free_pipeline(t_command *pipeline);

// main_ext.c
char		*shell_read_line(void);
void		print_tokens(t_token *tokens);
void		print_pipeline(t_command *pipeline);

// signals
void		setup_signals(void);

// utils.c
void		ft_getcwd(char *buf, size_t size);
void		printbanner(void);
bool		is_spaces(char c);

#endif
