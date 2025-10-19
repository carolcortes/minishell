/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 13:43:19 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sysexits.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>

# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

/* Global variable used as a flag to handle asynchronous signals safely.
Declared as 'volatile sig_atomic_t' to ensure atomic access and prevent compiler
optimizations that could cause unexpected behaviour in signal handlers. */
extern volatile sig_atomic_t	g_signal;

/* ANSI Color codes */
# define Y		"\033[1;33m"
# define G		"\033[1;32m"
# define C 		"\033[1;36m"
# define RED	"\033[1;31m"
# define MAG	"\033[1;95m"
# define RST 	"\033[0m"

# define WHITESPACES "\t\n\v\f\r "

/*============================================================================
Token Structure
==============================================================================
Represents a lexical unit (token) of a user input command.
It can be a word (command name or argument) or a special operator
(pipe, redirection). Each token carries information about how it
should be handled by the parser and executor.
char	*value;
bool	allow_expand; //$home: /home/cassiano
bool	is_pipe;
bool	is_redirection;	// true se for >, >>, <
int		redir_type;		// 1: >, 2: >>, 3: <, 0: nenhum
=============================================================================*/
typedef struct s_token
{
	char	*value;
	bool	allow_expand;
	bool	is_pipe;
	bool	is_redirection;
	int		redir_type;
}	t_token;

/*============================================================================
Shell Structure
==============================================================================
Represents the shell state, including the environment and the status
of the last executed command. This struct replaces the use of
the global variable g_last_status.
char	**envp;          // ambiente duplicado
int		last_status;	// substitui g_last_status
=============================================================================*/
typedef struct s_shell
{
	char	**envp;
	int		last_status;
}	t_shell;

/*============================================================================
Builtin Structure
==============================================================================
Represents a builtin command. It allows the shell to quickly call
the correct function without a large if/else or switch statement.
==============================================================================*/
typedef struct s_builtin
{
	const char	*builtin_name;
	int			(*builtin)(t_token **av, char **envp);
}	t_builtin;

/*============================================================================
Redirection Structure
==============================================================================
Represents a redirection for a command. It helps the shell open
the correct files and apply the appropriate dup2 before executing
the command.
int		type;		1: >, 2: >>, 3: <, 4: <<
char	*filename;	para << será o delimitador
==============================================================================*/
typedef struct s_redirection
{
	int		type;
	char	*filename;
}	t_redirection;

/*============================================================================
Command Structure
==============================================================================
Represents a complete command, including its arguments and redirections.
It can be linked to other commands via next/prev pointers to form pipelines.

Example:
	Input: cat file.txt | grep hello
	t_command 1:
		args: ["cat", "file.txt"]
		redir_count = 0
	t_command 2:
		args: ["grep", "hello"]
		redir_count = 0
		prev points to cat

t_token				**args;		Array of tokens for this command
int					argc;		Number of arguments
t_redirection		*redirs;	Array of redirections
int					redir_count;	Number of redirections
struct s_command	*next;		Next command in the pipeline
struct s_command	*prev;		Previous command (optional)
==============================================================================*/
typedef struct s_command
{
	t_token				**args;
	int					argc;
	t_redirection		*redirs;
	int					redir_count;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

/*============================================================================
Execution Data Structure
==============================================================================
Used to manage the execution of pipelines. Stores information needed
to set up pipes, track process IDs, and provide environment variables.
int		*input_fd;		Input file descriptor for the current command
int		pipe_fd[2];		Pipe created for communication between commands
pid_t	*last_pid;		Last process created (used with waitpid)
char	**envp;			Shell environment
==============================================================================*/
typedef struct s_exec_data
{
	int			*input_fd;
	int			pipe_fd[2];
	pid_t		*last_pid;
	char		**envp;
}	t_exec_data;

/*============================================================================
Token Data Structure
==============================================================================
Used to manage a dynamic array of tokens. Prevents manual reallocation
every time a new token is added.
t_token	*tokens;		Array of tokens
int		count;			Number of tokens currently stored
int		capacity;		Maximum capacity of the array
==============================================================================*/
typedef struct s_token_data
{
	t_token	*tokens;
	int		count;
	int		capacity;
}	t_token_data;

/*============================================================================
Quote Data Structure
==============================================================================
Used to handle parsing of quoted strings (' ' and " "). Stores the final
token and whether variable expansion is allowed inside it.
char	**token;			The resulting token after parsing
bool	*allow_expand;		Indicates if expansion is allowed within this token
==============================================================================*/
typedef struct s_quote_data
{
	char	**token;
	bool	*allow_expand;
}	t_quote_data;

/*============================================================================
Process Data Structure
==============================================================================
A variation used to organize execution data. Essentially the same as
t_exec_data but can be used in a different context, for example, a
separate function to manage child processes.
int		*input_fd;		Input file descriptor for the current command
int		pipe_fd[2];		Pipe used for communication between commands
pid_t	*last_pid;		Last process created (used with waitpid)
==============================================================================*/
typedef struct s_process_data
{
	int			*input_fd;
	int			pipe_fd[2];
	pid_t		*last_pid;
}	t_process_data;

/* builtins */
int			exec_builtin(t_token **args, char **envp);
int			ft_echo(t_token **args, char **envp);
int			ft_cd(t_token **args, char **envp);
int			ft_pwd(t_token **args, char **envp);
int			ft_export(t_token **args, char **envp);
int			ft_unset(t_token **args, char **envp);
int			ft_env(t_token **args, char **envp);
int			ft_exit(t_token **args, char **envp);

/* ft_export_ext.c */
int			add_or_update_env(char *var, char **envp);
int			append_env_var(char **envp, char *key, char *value);

/* ft_export_ext2.c */
char		*create_new_var(char *key, char *old_value, char *value);
int			append_to_existing(char **envp, int i, char *key, char *value);

/* ft_env.c */
char		**dup_env(char **envp);

/* execution
execute_pip_ext1.c */
void		handle_child_process(t_command *cmd, int input_fd,
				int pipe_fd[2], t_shell *shell);

/* execute_pipeline.c */
void		execute_pipeline(t_command *pipeline, t_shell *shell);

/* external_ext.c */
void		exec_child(char *path, char **argv, char **envp);

/* external.c */
int			execute_external(t_token **args, t_shell *shell);

/* heredoc.c */
char		*handle_heredoc(char *delimiter, bool allow_expand, t_shell *shell);

/* path.c */
char		*find_command_path(char *command, char **envp);

/*		redirections.c */
int			apply_redirections(t_command *cmd);

/* redirections_ext.c */
int			open_output_file(char *filename, int append);
int			open_input_file(char *filename);

/* exec_utils.c */
bool		is_builtin(t_token **args);
char		**tokens_to_argv(t_token **tokens);

/* parsing
   pipeline_ext.c */
t_token		**copy_command_args(t_token *tokens, int start, int count);
int			count_args_until_pipe(t_token *tokens, int start_index);

/* pipeline.c */
t_command	*parse_pipeline(t_token *tokens, t_shell *shell);

/* tokens.c */
t_token		*shell_split_line_quotes(char *line);

/* tokens_ext1.c */
bool		expand_token_array(t_token_data *data);
bool		process_special_char(char *line, int *i, t_token_data *data);
char		*extract_quoted(const char *line, int *i, bool *allow_expand);

/* tokens_ext2.c */
bool		process_word_token(char *line, int *i, t_token_data *data);

/* tokens_ext3.c */
bool		is_special_char(char c);
t_token		create_pipe_token(void);
t_token		create_redirection_token(char *value, int type);

/* redir_parse_ext.c */
void		add_redirection(t_command *cmd, int type, char *filename);

/* redir_parse.c */
void		extract_redirections(t_command *cmd, t_shell *shell);

/* expand.c */
char		*expand_variables(const char *str, t_shell *shell);
void		expand_tokens(t_token *tokens, t_shell *shell);

/* expand_ext.c */
bool		token_has_variable(const char *str);
void		remove_empty_expanded_tokens(t_token *tokens);

/* free.c */
void		free_strings(char **arr);
void		free_tokens(t_token *tokens);
char		*ft_strjoin_free(char *s1, char *s2, int mode);
void		free_pipeline(t_command *pipeline);

/* main_ext.c */
int			handle_child_process_single(t_command *cmd, t_shell *shell);
void		handle_parent_process(pid_t pid, t_shell *shell);
char		*shell_read_line(void);
void		print_tokens(t_token *tokens);
void		print_pipeline(t_command *pipeline);

/* signals.c */
void		setup_signals(void);
void		setup_child_signals(void);
void		setup_wait_signals(void);

/* utils.c */
void		ft_getcwd(char *buf, size_t size);
void		printbanner(void);
bool		is_spaces(char c);

#endif
