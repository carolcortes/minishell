/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/19 21:45:52 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"
//#include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_display_prompt
//#include <readline/history.h> // add_history, clear_history, history_expand

t_builtin	g_builtin[] =
{
	// {.builtin_name = "echo", .foo=cell_echo},   // Echo text to stdout
	// {.builtin_name = "env", .foo=cell_env},     // Print environment
	{.builtin_name = "exit", .foo=shell_exit},  // Exit the shell
	{.builtin_name = NULL},                    	// Sentinel
};


/*
** Função auxiliar ft_strjoin_free:
** Junta duas strings e libera as originais dependendo do 'mode':
** mode = 1 -> libera s1
** mode = 2 -> libera s2
** mode = 3 -> libera s1 e s2
*/
char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (result);
}

char	*expand_variables(const char *str, int last_status)
{
	int		i = 0;
	char	*result = ft_strdup("");
	char	*tmp;

	while (str[i])
	{
		if (str[i] == '$')
		{
			// 1. Trata $? (último status)
			if (str[i + 1] == '?')
			{
				tmp = ft_itoa(last_status);
				result = ft_strjoin_free(result, tmp, 3);
				i += 2;
			}
			// 2. Trata variáveis normais $VAR
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				int start = ++i; // pula o $
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				char *var_name = ft_substr(str, start, i - start);
				char *var_value = getenv(var_name);
				if (var_value)
					result = ft_strjoin_free(result, ft_strdup(var_value), 3);
				free(var_name);
			}
			// 3. Apenas um $ solto → copia literal
			else
			{
				result = ft_strjoin_free(result, ft_substr(str, i, 1), 3);
				i++;
			}
		}
		else
		{
			// Copia caractere literal
			result = ft_strjoin_free(result, ft_substr(str, i, 1), 3);
			i++;
		}
	}
	return (result);
}

char *shell_read_line(void)
{
    char *line;

    line = readline("🏴‍☠️ minishell 🏴‍☠️ $> "); // É preciso dar um free
    if (!line) // ctrl-D → retorna NULL
    {
        printf("exit\n");
        return (NULL);
    }
    if (*line) // adiciona ao histórico se não for vazio
        add_history(line);
    return line; // precisa ser liberado com free()
}

static bool	is_spaces(char c)
{
	int	i;

	i = 0;
	while (WHITESPACES[i])
	{
		if (c == WHITESPACES[i])
			return (true);
		i++;
	}
	return (false);
}

typedef struct s_token
{
    char *value;
    bool allow_expand; // true para aspas duplas ou sem aspas, false para aspas simples
}   t_token;

static char *extract_quoted(const char *line, int *i, bool *allow_expand)
{
    char quote = line[*i];
    int start;
    char *result;

    if (quote == '\'')
        *allow_expand = false;
    else if (quote == '"')
        *allow_expand = true;

    (*i)++; // pula a aspa inicial
    start = *i;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    if (!line[*i])
        return (NULL); // aspas não fechadas
    result = ft_substr(line, start, *i - start);
    (*i)++; // pula a aspa final
    return (result);
}

t_token *shell_split_line_quotes(char *line)
{
    int i = 0, count = 0, capacity = 8;
    t_token *tokens = malloc(sizeof(t_token) * capacity);

    if (!tokens)
        return (NULL);

    while (line[i])
    {
        while (line[i] && is_spaces(line[i]))
            i++;
        if (!line[i])
            break;

        char *token = ft_strdup("");
        bool allow_expand = true;

        while (line[i] && !is_spaces(line[i]))
        {
            if (line[i] == '\'' || line[i] == '"')
            {
                bool local_expand;
                char *part = extract_quoted(line, &i, &local_expand);
                if (!part)
                {
                    printf("Syntax error: unclosed quote\n");
                    // liberar memória já alocada
                    return (NULL);
                }
                if (!local_expand)
                    allow_expand = false; // se tiver parte com aspas simples, bloqueia expansão
                token = ft_strjoin_free(token, part, 3);
            }
            else
            {
                char *part = ft_substr(line, i, 1);
                token = ft_strjoin_free(token, part, 3);
                i++;
            }
        }

        if (count >= capacity - 1)
        {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(t_token) * capacity);
        }
        tokens[count].value = token;
        tokens[count].allow_expand = allow_expand;
        count++;
    }
    tokens[count].value = NULL;
    tokens[count].allow_expand = false;
    return tokens;
}

void expand_tokens(t_token *tokens, int last_status)
{
	(void)last_status; // evita warning
    for (int i = 0; tokens[i].value; i++)
    {
        if (tokens[i].allow_expand)
        {
            char *expanded = expand_variables(tokens[i].value, last_status);

            free(tokens[i].value);
            tokens[i].value = expanded;
        }
    }
}


int	main(void)
{
	char	*line;
	t_token *args;
	int		i;

	line = NULL;
	printbanner();
	setup_signals();
	while ((line = shell_read_line()) != NULL)
	{

		//shell_find_delim(line);
		args = shell_split_line_quotes(line);
		if (!args)
		{
			free(line); // modificado para liberar memória em caso de erro
			continue;
		}


		// Expande variáveis antes de imprimir
		expand_tokens(args, 0); // passar last_status real depois

		// Percorre e imprime cada argumento
		i = 0;
		while (args[i].value)
		{
			printf("arg[%d]: %s\n", i, args[i].value);
			i++;
		}

		// Libera memória
		i = 0;
		while (args[i].value)
			free(args[i++].value);
		free(args);
		free(line);
	}
	return (EXIT_SUCCESS);
}
