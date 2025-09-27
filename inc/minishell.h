/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:32 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/27 17:22:23 by cgross-s         ###   ########.fr       */
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
# include <fcntl.h>    // For O_WRONLY, O_RDONLY ... open()

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

// Finalidade → É a base do parser, contém a informação de cada palavra ou operador.
typedef struct s_token
{
	char	*value;
	bool	allow_expand;
	bool	is_pipe;
	bool	is_redirection;	// true se for >, >>, <
	int		redir_type;		// 1: >, 2: >>, 3: <, 0: nenhum
}	t_token;

// Finalidade → Permite chamar rapidamente a função correta sem if/else gigante.
typedef struct s_builtin
{
	const char	*builtin_name;
	int			(*builtin)(t_token **av, char **envp); // ✅ Adicionar envp
}	t_builtin;

// Finalidade → Facilita abrir e aplicar os dup2 corretos antes de executar o comando.
typedef struct s_redirection
{
	int		type;		// 1: >, 2: >>, 3: <
	char	*filename;	// arquivo alvo
}	t_redirection;

/*
- Estrutura de nível mais alto: 
	representa um comando completo (com args e redirecionamentos).
- Pode estar ligado a outros via next/prev → pipelines.
- Exemplo:
	- Input: cat file.txt | grep hello
	- t_command 1:
		- args: ["cat", "file.txt"]
		- redir_count=0
	- t_command 2:
		- args: ["grep", "hello"]
		- redir_count=0
		- prev aponta para cat.
*/
// Finalidade → É a estrutura central da execução.
typedef struct s_command
{
	t_token				**args;		// Array de tokens deste comando
	int					argc;		// Número de argumentos
	t_redirection		*redirs;	// array de redirecionamentos
	int					redir_count;
	struct s_command	*next;		// Próximo comando na pipeline
	struct s_command	*prev;		// Comando anterior (opcional)
}	t_command;

// Usado para controlar a execução de pipelines.
typedef struct s_exec_data
{
	int			*input_fd;	// entrada do comando atual (normalmente stdin ou saída do comando anterior).
	int			pipe_fd[2];	// pipe criado para comunicação entre comandos.
	pid_t		*last_pid;	// último processo criado (para o waitpid).
	char		**envp;		// ambiente do shell.
}	t_exec_data;

// usado quando crias um novo processo com fork.
typedef struct s_fork_data
{
	int			input_fd;
	int			pipe_fd[2];
	pid_t		*last_pid;
	char		**envp;
}	t_fork_data;

// Finalidade → Evita realocação manual a cada token novo.
typedef struct s_token_data
{
	t_token	*tokens;
	int		count;
	int		capacity;
}	t_token_data;

// Usado para parsing com aspas (' ' e " ").
typedef struct s_quote_data
{
	char	**token;		// O token final (token).
	bool	*allow_expand;	// Se dentro desse token é permitido expandir
}	t_quote_data;

/*Mais uma variação para organizar dados da execução.
É essencialmente igual a t_exec_data, mas pode ser usado em outro 
contexto (ex: função separada para gerir child processes).*/
typedef struct s_process_data
{
	int			*input_fd;
	int			pipe_fd[2];
	pid_t		*last_pid;
	char		**envp;
}	t_process_data;

// substitui a variável global g_last_status
typedef struct s_shell
{
	//char	**envp;          // ambiente duplicado
	int		last_status;    // substitui g_last_status
}	t_shell;


//	builtins
int			exec_builtin(t_token **args, char **envp); // ✅ char **envp
int			ft_cd(t_token **args, char **envp);
int			ft_echo(t_token **args, char **envp);
int			ft_env(t_token **args, char **envp);
char		**dup_env(char **envp);
void		free_env(char **env);
int			ft_exit(t_token **args, char **envp);
//		ft_export_ext.c
int			update_env_var(char **envp, char *key, char *var);
int			add_env_var(char *var, char **envp);
int			add_or_update_env(char *var, char **envp);
//		ft_export.c
int			ft_export(t_token **args, char **envp);

int			ft_pwd(t_token **args, char **envp);
int			ft_unset(t_token **args, char **envp);

//	execution
//		execute_pip_ext1.c
void		execute_command(t_command *cmd, char **envp);
void		handle_child_process(t_command *cmd, int input_fd,
				int pipe_fd[2], char **envp);
void		update_fds_after_command(t_command *cmd, t_exec_data *data);
//		execute_pip_ext2.c
void		redirect_input(int input_fd);
void		redirect_output(int pipe_fd[2]);
//		execute_pipeline.c
//void		execute_pipeline(t_command *pipeline, char **envp);
void		execute_pipeline(t_command *pipeline, char **envp, t_shell *shell);
//		external.c
int			execute_external(t_token **args, char **envp);
//		path.c
char		*find_command_path(char *command, char **envp);
//		redirections_ext.c
int			open_output_file(char *filename, int append);
int			open_input_file(char *filename);
//		redirections.c
int			apply_redirections(t_command *cmd);
//		utils.c
bool		is_builtin(t_token **args);
char		**tokens_to_argv(t_token **tokens);
void		free_argv(char **argv);

//	parsing
//		pipeline_ext.c
int			count_args_until_pipe(t_token *tokens, int start_index);
//		pipeline.c
t_command	*parse_pipeline(t_token *tokens);
//		tokens.c
t_token		*shell_split_line_quotes(char *line);
//		tokens_ext1.c
//bool		is_special_char(char c);
//t_token		create_pipe_token(void);
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
//		tokens_ext3.c
bool		is_special_char(char c);
t_token		create_pipe_token(void);
t_token		create_redirection_token(char *value, int type);
//		redirections.c
void		extract_redirections(t_command *cmd);

// expand.c
void		expand_tokens(t_token *tokens, int last_status);

// free.c
void		free_array(char **arr);
void		free_tokens(t_token *tokens);
char		*ft_strjoin_free(char *s1, char *s2, int mode);
void		free_pipeline(t_command *pipeline);

// main_ext.c
int			handle_child_process_single(t_command *cmd, char **env);
//void		handle_parent_process(pid_t pid);
void		handle_parent_process(pid_t pid, t_shell *shell);
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
