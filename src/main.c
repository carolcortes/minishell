/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/28 11:46:29 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	execute_with_redirections(t_command *cmd, char **env, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(handle_child_process_single(cmd, env));
	else if (pid > 0)
		handle_parent_process(pid, shell);
	else
	{
		perror("minishell: fork");
		shell->last_status = 1;
	}
}

static void	process_single_command(t_command *cmd, char **env, t_shell *shell)
{
	if (cmd->redir_count > 0)
		execute_with_redirections(cmd, env, shell);
	else
	{
		if (is_builtin(cmd->args))
			shell->last_status = exec_builtin(cmd->args, env);
		else
			shell->last_status = execute_external(cmd->args, env);
	}
}

static void	process_input_line(char *line, char **env, t_shell *shell)
{
	t_token		*tokens;
	t_command	*pipeline;

	tokens = shell_split_line_quotes(line);
	free(line);
	if (!tokens)
		return ;
	expand_tokens(tokens, shell->last_status);
	pipeline = parse_pipeline(tokens);
	if (pipeline)
	{
		if (pipeline->next)
			execute_pipeline(pipeline, env, shell);
		else
			process_single_command(pipeline, env, shell);
		free_pipeline(pipeline);
	}
	free_tokens(tokens);
}

static void	main_loop(char **env, t_shell *shell)
{
	char	*line;

	while (42)
	{
		line = shell_read_line();
		if (!line)
			break ;
		process_input_line(line, env, shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	t_shell	shell;

	(void)argc;
	(void)argv;
	env = dup_env(envp);
	shell.last_status = 0;
	printbanner();
	setup_signals();
	main_loop(env, &shell);
	free_env(env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
