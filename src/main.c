/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:20 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*static void	process_single_command(t_command *pipeline, t_shell *shell,
	t_token *tokens)
{
	if (pipeline->argc == 0)
	{
		if (pipeline->redir_count > 0)
		{
			apply_redirections(pipeline, shell, tokens);
		}
		return ;
	}
	if (pipeline->redir_count > 0)
		execute_with_redirections(pipeline, shell, tokens);
	else
	{
		if (is_builtin(pipeline->args))
		{
			int	status;

			status = exec_builtin(pipeline->args, shell->envp);
			if (status < 0)
			{
				int	exit_code;

				exit_code = -(status + 1);
				free_pipeline(pipeline);
				free_tokens(tokens);
				free_strings(shell->envp);
				rl_clear_history();
				exit(exit_code);
			}
			shell->last_status = status;
		}
		else
			shell->last_status = execute_external(pipeline->args, shell);
	}
}*/

/*static void	process_single_command(t_command *pipeline, t_shell *shell,
	t_token *tokens)
{
	int	status;

	if (pipeline->argc == 0)
	{
		if (pipeline->redir_count > 0)
			apply_redirections(pipeline, shell, tokens);
		return ;
	}
	////
	if (pipeline->redir_count > 0)
		return (execute_with_redirections(pipeline, shell, tokens));
	//if (pipeline->redir_count > 0)
	//{
	//	execute_with_redirections(pipeline, shell, tokens);
	//	return ;
	//}
	if (is_builtin(pipeline->args))
	{
		status = exec_builtin(pipeline->args, shell->envp);
		handle_builtin_exit(pipeline, shell, tokens, status);
	}
	else
		shell->last_status = execute_external(pipeline->args, shell);
}*/

static void	process_single_command(
	t_command *pipeline,
	t_shell *shell,
	t_token *tokens)
{
	int	status;

	if (pipeline->argc == 0)
	{
		if (pipeline->redir_count > 0)
			apply_redirections(pipeline, shell, tokens);
		return ;
	}
	if (pipeline->redir_count > 0)
	{
		execute_with_redirections(pipeline, shell, tokens);
		return ;
	}
	if (is_builtin(pipeline->args))
	{
		status = exec_builtin(pipeline->args, shell->envp);
		handle_builtin_exit(pipeline, shell, tokens, status);
	}
	else
		shell->last_status = execute_external(pipeline->args, shell);
}

static void	handle_pipeline_result(t_command *pipeline, t_shell *shell,
	t_token *tokens)
{
	if (pipeline == (t_command *)-1)
	{
		shell->last_status = 2;
		free_tokens(tokens);
		return ;
	}
	if (!pipeline)
	{
		free_tokens(tokens);
		return ;
	}
	if (pipeline->next)
		execute_pipeline(pipeline, shell, tokens);
	else
		process_single_command(pipeline, shell, tokens);
	free_pipeline(pipeline);
	free_tokens(tokens);
}

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
	handle_pipeline_result(pipeline, shell, tokens);
}

static void	main_loop(t_shell *shell)
{
	char	*line;

	while (42)
	{
		setup_signals();
		line = shell_read_line();
		if (g_signal == SIGINT)
		{
			shell->last_status = 130;
			g_signal = 0;
			if (line && !*line)
			{
				free(line);
				continue ;
			}
		}
		if (!line)
			break ;
		process_input_line(line, shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.envp = dup_env(envp);
	shell.last_status = 0;
	shell.first_pipeline_command = NULL;
	if (argc >= 3 && ft_strcmp(argv[1], "-c") == 0)
	{
		setup_signals();
		process_input_line(ft_strdup(argv[2]), &shell);
		free_strings(shell.envp);
		return (shell.last_status);
	}
	setup_signals();
	main_loop(&shell);
	free_strings(shell.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
