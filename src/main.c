/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/18 16:14:01 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//static void	execute_with_redirections(t_command *cmd, char **env,
//	t_shell *shell)
// exit(handle_child_process_single(cmd, shell->envp));
static void	execute_with_redirections(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		exit(handle_child_process_single(cmd, shell));
	}
	else if (pid > 0)
		handle_parent_process(pid, shell);
	else
	{
		perror("minishell: fork");
		shell->last_status = 1;
	}
}

//static void	process_single_command(t_command *cmd, char **env, 
//t_shell *shell)
//execute_with_redirections(cmd, env, shell);
//execute_with_redirections(cmd, shell->envp, shell);
//shell->last_status = exec_builtin(cmd->args, env);
//shell->last_status = execute_external(cmd->args, shell->envp);
static void	process_single_command(t_command *cmd, t_shell *shell)
{
	if (cmd->argc == 0)
	{
		if (cmd->redir_count > 0)
		{
			if (!apply_redirections(cmd))
				shell->last_status = 1;
			else
				shell->last_status = 0;
		}
		return ;
	}
	if (cmd->redir_count > 0)
		execute_with_redirections(cmd, shell);
	else
	{
		if (is_builtin(cmd->args))
			shell->last_status = exec_builtin(cmd->args, shell->envp);
		else
			shell->last_status = execute_external(cmd->args, shell);
	}
}

//static void	process_input_line(char *line, char **env, t_shell *shell)
//execute_pipeline(pipeline, env, shell);
//execute_pipeline(pipeline, shell->envp, shell);
//process_single_command(pipeline, env, shell);
//process_single_command(pipeline, shell->envp, shell);
static void	process_input_line(char *line, t_shell *shell)
{
	t_token		*tokens;
	t_command	*pipeline;

	tokens = shell_split_line_quotes(line);
	free(line);
	if (!tokens)
		return ;
	expand_tokens(tokens, shell);
	pipeline = parse_pipeline(tokens, shell);
	if (pipeline)
	{
		if (pipeline->next)
			execute_pipeline(pipeline, shell);
		else
			process_single_command(pipeline, shell);
		free_pipeline(pipeline);
	}
	free_tokens(tokens);
}

//static void	main_loop(char **env, t_shell *shell)
//process_input_line(line, shell->envp, shell);
//process_input_line(line, env, shell);
static void	main_loop(t_shell *shell)
{
	char	*line;

	while (42)
	{
		setup_signals();
		if (g_signal == SIGINT)
			g_signal = 0;
		line = shell_read_line();
		if (!line)
			break ;
		process_input_line(line, shell);
	}
}

//char	**env;
//env = dup_env(envp);
//main_loop(env, &shell);
//free_env(env);
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.envp = dup_env(envp);
	shell.last_status = 0;
	printbanner();
	setup_signals();
	main_loop(&shell);
	free_env(shell.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
