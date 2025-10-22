/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/21 22:19:56 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	update_pwd_vars(char **envp, const char *oldpwd, const char *newpwd)
{
	char	*kv;
	char	*tmp;
	int		status;

	status = 0;
	if (oldpwd)
	{
		tmp = ft_strjoin("OLDPWD=", oldpwd);
		if (!tmp)
			return (1);
		status |= add_or_update_env(tmp, envp);
		free(tmp);
	}
	if (newpwd)
	{
		kv = ft_strjoin("PWD=", newpwd);
		if (!kv)
			return (1);
		status |= add_or_update_env(kv, envp);
		free(kv);
	}
	return (status != 0);
}

static int	cd_target_from_key(char **envp, const char *key,
				char **target, int *print_after)
{
	*target = env_get_value(envp, key);
	if (!*target)
	{
		fprintf(stderr, "minishell: cd: %s not set\n", key);
		return (1);
	}
	if (print_after && ft_strcmp(key, "OLDPWD") == 0)
		*print_after = 1;
	return (0);
}

static int	cd_handle_dash_option(t_token **args,
				char **envp, char **target, int *print_after)
{
	int	argc;

	argc = get_token_count(args);
	if (ft_strcmp(args[1]->value, "--") == 0)
	{
		if (argc == 2)
			return (cd_target_from_key(envp, "HOME", target, print_after));
		else if (argc == 3)
		{
			*target = args[2]->value;
			return (0);
		}
		return (fprintf(stderr, "minishell: cd: too many arguments\n"), 1);
	}
	if (ft_strcmp(args[1]->value, "-") == 0)
	{
		if (argc > 2)
			return (fprintf(stderr, "minishell: cd: too many arguments\n"), 1);
		return (cd_target_from_key(envp, "OLDPWD", target, print_after));
	}
	return (-1);
}

static int	cd_resolve_target(t_token **args, char **envp,
					char **target, int *print_after)
{
	int	argc;
	int	status;

	*print_after = 0;
	argc = get_token_count(args);
	if (argc == 1)
		return (cd_target_from_key(envp, "HOME", target, print_after));
	{
		status = cd_handle_dash_option(args, envp, target, print_after);
		if (status != -1)
			return (status);
	}
	if (argc > 2)
		return (fprintf(stderr, "minishell: cd: too many arguments\n"), 1);
	*target = args[1]->value;
	return (0);
}

int	ft_cd(t_token **args, char **envp)
{
	char		*target;
	char		*oldpwd;
	char		*newpwd;
	int			print_after;

	oldpwd = getcwd(NULL, 0);
	if (cd_resolve_target(args, envp, &target, &print_after))
		return (free(oldpwd), 1);
	if (chdir(target) != 0)
	{
		fprintf(stderr, "minishell: cd: %s: %s\n", target, strerror(errno));
		return (free(oldpwd), 1);
	}
	newpwd = getcwd(NULL, 0);
	if (update_pwd_vars(envp, oldpwd, newpwd))
		return (free(oldpwd), free(newpwd), 1);
	if (print_after && newpwd)
		printf("%s\n", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
