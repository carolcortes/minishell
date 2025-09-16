/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/16 17:27:58 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../inc/minishell.h"

// Variável global para o último status (como permite o subject)
int g_last_status = 0;  // ✅ DEFINIÇÃO real da variável

char	*shell_read_line(void)
{
	char	*line;

	line = readline(MAG"🏴‍☠️  minishell 🏴‍☠️ $> "RST);
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

// Adicione esta função para verificar o parsing
void	print_tokens(t_token *tokens)
{
	int	i = 0;
	
	printf("=== TOKENS PARSED ===\n");
	while (tokens[i].value)
	{
		printf("Token %d: '%s' (expand: %d, pipe: %d, redir: %d)\n",
			i, tokens[i].value, tokens[i].allow_expand,
			tokens[i].is_pipe, tokens[i].is_redirection);
		i++;
	}
	printf("=====================\n");
}

void	print_pipeline(t_command *pipeline)
{
	t_command *cmd = pipeline;
	int cmd_index = 0;
	
	printf("=== PIPELINE STRUCTURE ===\n");
	while (cmd)
	{
		printf("Command %d: ", cmd_index++);
		for (int i = 0; i < cmd->argc; i++)
		{
			printf("'%s' ", cmd->args[i]->value);
		}
		printf("\n");
		cmd = cmd->next;
	}
	printf("==========================\n");
}

// No main.c, modifique o loop principal:
int	main(int argc, char **argv, char **envp)
{
	char        *line;
	t_token     *tokens;
	t_command   *pipeline;
	char        **env;

	(void)argc;
	(void)argv;
	env = dup_env(envp);
	line = NULL;
	printbanner();
	setup_signals();
	while (42)
	{
		line = shell_read_line();
		if (!line)
			break;
		tokens = shell_split_line_quotes(line);
		free(line);
		if (!tokens)
			continue;
		expand_tokens(tokens, g_last_status); // ✅ Passa o último status
		print_tokens(tokens); // Debug: mostra tokens parseados
		pipeline = parse_pipeline(tokens);
		if (pipeline)
		{
			print_pipeline(pipeline); // Debug
			if (pipeline->next) // Se for pipeline
				execute_pipeline(pipeline, env);
			else // Comando único
			{
				if (is_builtin(pipeline->args))
					g_last_status = exec_builtin(pipeline->
					args, env); // ✅ Deve retornar int
				else
					g_last_status = execute_external(pipeline->
					args, env); // ✅ External retorna int
			}
			free_pipeline(pipeline);
		}
		free_tokens(tokens);
	}
	free_env(env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}*/

#include "../inc/minishell.h"

int	g_last_status = 0;

char	*shell_read_line(void)
{
	char	*line;

	line = readline(MAG"🏴‍☠️  minishell 🏴‍☠️ $> "RST);
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("=== TOKENS PARSED ===\n");
	while (tokens[i].value)
	{
		printf("Token %d: '%s' (expand: %d, pipe: %d, redir: %d)\n",
			i, tokens[i].value, tokens[i].allow_expand,
			tokens[i].is_pipe, tokens[i].is_redirection);
		i++;
	}
	printf("=====================\n");
}

void	print_pipeline(t_command *pipeline)
{
	t_command	*cmd;
	int			cmd_index;
	int			i;

	cmd = pipeline;
	cmd_index = 0;
	printf("=== PIPELINE STRUCTURE ===\n");
	while (cmd)
	{
		printf("Command %d: ", cmd_index++);
		i = 0;
		while (i < cmd->argc)
		{
			printf("'%s' ", cmd->args[i]->value);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
	printf("==========================\n");
}

static void	process_single_command(t_command *pipeline, char **env)
{
	if (is_builtin(pipeline->args))
		g_last_status = exec_builtin(pipeline->args, env);
	else
		g_last_status = execute_external(pipeline->args, env);
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
	print_tokens(tokens);
	pipeline = parse_pipeline(tokens);
	if (pipeline)
	{
		print_pipeline(pipeline);
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
