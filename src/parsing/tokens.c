/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/11 16:54:46 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* ========== DECLARAÇÕES ANTECIPADAS ========== */
static bool	is_special_char(char c);
static t_token	create_pipe_token(void);
static bool	process_special_char(char *line, int *i, t_token **tokens, 
                                int *count, int *capacity);

/* ========== FUNÇÕES AUXILIARES ========== */
static bool	is_special_char(char c)
{
	return (c == '|');
}

static t_token	create_pipe_token(void)
{
	t_token	pipe_token;

	pipe_token.value = ft_strdup("|");
	pipe_token.allow_expand = false;
	pipe_token.is_pipe = true;
	pipe_token.is_redirection = false;
	return (pipe_token);
}

static bool	process_special_char(char *line, int *i, t_token **tokens, 
                                int *count, int *capacity)
{
	t_token	*new_tokens;
	t_token	special_token;

	if (line[*i] == '|')
		special_token = create_pipe_token();
	else
	{
		(*i)++;
		return (true);
	}

	if (*count >= *capacity - 1)
	{
		*capacity *= 2;
		new_tokens = realloc(*tokens, sizeof(t_token) * (*capacity));
		if (!new_tokens)
			return (false);
		*tokens = new_tokens;
	}

	(*tokens)[*count] = special_token;
	(*count)++;
	(*i)++;
	return (true);
}

/* ========== FUNÇÕES ORIGINAIS (MANTENHA APENAS UMA VERSÃO) ========== */
static char	*extract_quoted(const char *line, int *i, bool *allow_expand)
{
	char	quote;
	int		start;
	char	*result;

	quote = line[*i];
	if (quote == '\'')
		*allow_expand = false;
	else if (quote == '"')
		*allow_expand = true;
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (NULL);
	result = ft_substr(line, start, *i - start);
	(*i)++;
	return (result);
}

static bool	process_quoted_part(char *line, int *i, char **token, bool *allow_expand)
{
	bool	local_expand;
	char	*part;

	part = extract_quoted(line, i, &local_expand);
	if (!part)
	{
		printf("Syntax error: unclosed quote\n");
		return (false);
	}
	if (!local_expand)
		*allow_expand = false;
	*token = ft_strjoin_free(*token, part, 3);
	return (true);
}

static bool	process_regular_char(char *line, int *i, char **token)
{
	char	*char_str;

	char_str = ft_substr(line, *i, 1);
	if (!char_str)
		return (false);
	*token = ft_strjoin_free(*token, char_str, 3);
	(*i)++;
	return (true);
}

/* ========== PROCESS_TOKEN (APENAS UMA VERSÃO) ========== */
static bool	process_token(char *line, int *i, t_token **tokens, int *count, int *capacity)
{
	char	*token;
	bool	allow_expand;
	t_token	*new_tokens;

	token = ft_strdup("");
	allow_expand = true;
	if (!token)
		return (false);
	
	// MODIFICAÇÃO: adicione a verificação de caracteres especiais
	while (line[*i] && !is_spaces(line[*i]) && !is_special_char(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (!process_quoted_part(line, i, &token, &allow_expand))
				return (free(token), false);
		}
		else
		{
			if (!process_regular_char(line, i, &token))
				return (free(token), false);
		}
	}

	if (*count >= *capacity - 1)
	{
		*capacity *= 2;
		new_tokens = realloc(*tokens, sizeof(t_token) * (*capacity));
		if (!new_tokens)
			return (free(token), false);
		*tokens = new_tokens;
	}
	
	(*tokens)[*count].value = token;
	(*tokens)[*count].allow_expand = allow_expand;
	(*tokens)[*count].is_pipe = false;
	(*tokens)[*count].is_redirection = false;
	(*count)++;
	return (true);
}

/* ========== FUNÇÃO PRINCIPAL ========== */
t_token	*shell_split_line_quotes(char *line)
{
	int		i;
	int		count;
	int		capacity;
	t_token	*tokens;

	i = 0;
	count = 0;
	capacity = 8;
	tokens = malloc(sizeof(t_token) * capacity);
	if (!tokens)
		return (NULL);
	
	// Inicializa o primeiro token
	tokens[0].value = NULL;
	
	while (line[i])
	{
		while (line[i] && is_spaces(line[i]))
			i++;
		
		if (!line[i])
			break;
		
		if (is_special_char(line[i]))
		{
			if (!process_special_char(line, &i, &tokens, &count, &capacity))
				return (free_tokens(tokens), NULL);
		}
		else
		{
			if (!process_token(line, &i, &tokens, &count, &capacity))
				return (free_tokens(tokens), NULL);
		}
	}
	
	tokens[count].value = NULL;
	tokens[count].allow_expand = false;
	tokens[count].is_pipe = false;
	tokens[count].is_redirection = false;
	return (tokens);
}
