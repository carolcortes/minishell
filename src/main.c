/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/09/11 15:18:00 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*3 functions*/

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

void print_pipeline(t_command *pipeline)
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
int main(int argc, char **argv, char **envp)
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
        
        expand_tokens(tokens, 0);
        print_tokens(tokens); // Debug: mostra tokens parseados
        
        // NOVO: Parse da pipeline
        pipeline = parse_pipeline(tokens);
        if (pipeline)
        {
            print_pipeline(pipeline); // Debug: mostra estrutura da pipeline
            
            if (pipeline->next) // Tem pipes!
            {
                printf("Pipeline detectada! Precisamos implementar execute_pipeline()\n");
                // execute_pipeline(pipeline, env); // TODO: Implementar
            }
            else // Comando único
            {
                if (pipeline->args[0]->value)
                {
                    if (!exec_builtin(pipeline->args, env))
                        printf("comando externo: %s\n", pipeline->args[0]->value);
                }
            }
            free_pipeline(pipeline);
        }
        free_tokens(tokens);
    }
    free_env(env);
    rl_clear_history();
    return (EXIT_SUCCESS);
}
