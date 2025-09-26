/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/26 10:22:42 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_last_status = 0;

static int	handle_child_process_single(t_command *cmd, char **env)
{
	if (!apply_redirections(cmd))
		return (1);
	if (is_builtin(cmd->args))
		return (exec_builtin(cmd->args, env));
	else
		return (execute_external(cmd->args, env));
}

static void	handle_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status = 128 + WTERMSIG(status);
}

static void	execute_with_redirections(t_command *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(handle_child_process_single(cmd, env));
	else if (pid > 0)
		handle_parent_process(pid);
	else
	{
		perror("minishell: fork");
		g_last_status = 1;
	}
}

static void	process_single_command(t_command *cmd, char **env)
{
	if (cmd->redir_count > 0)
		execute_with_redirections(cmd, env);
	else
	{
		if (is_builtin(cmd->args))
			g_last_status = exec_builtin(cmd->args, env);
		else
			g_last_status = execute_external(cmd->args, env);
	}
}

static void	process_input_line(char *line, char **env)
{
	t_token		*tokens;
	t_command	*pipeline;

	tokens = shell_split_line_quotes(line);
	free(line);
	if (!tokens)
		return ;
	expand_tokens(tokens, g_last_status);
	pipeline = parse_pipeline(tokens);
	if (pipeline)
	{
		if (pipeline->next)
			execute_pipeline(pipeline, env);
		else
			process_single_command(pipeline, env);
		free_pipeline(pipeline);
	}
	free_tokens(tokens);
}

static void	main_loop(char **env)
{
	char	*line;

	while (42)
	{
		line = shell_read_line();
		if (!line)
			break ;
		process_input_line(line, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = dup_env(envp);
	printbanner();
	setup_signals();
	main_loop(env);
	free_env(env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
