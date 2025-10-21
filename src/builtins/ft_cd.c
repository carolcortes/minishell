/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/20 22:36:55 by cade-oli         ###   ########.fr       */
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

static int	cd_target_from_home(char **envp, char **target)
{
	*target = env_get_value(envp, "HOME");
	if (!*target)
	{
		fprintf(stderr, "minishell: cd: HOME not set\n");
		return (1);
	}
	return (0);
}

static int	cd_target_from_oldpwd(char **envp, char **target, int *print_after)
{
	*target = env_get_value(envp, "OLDPWD");
	if (!*target)
	{
		fprintf(stderr, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	*print_after = 1;
	return (0);
}

static int	cd_resolve_target(t_token **args, char **envp,
					char **target, int *print_after)
{
	*print_after = 0;
	if (args[2])
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (!args[1] || (args[1] && ft_strcmp(args[1]->value, "--") == 0))
		return (cd_target_from_home(envp, target));
	if (ft_strcmp(args[1]->value, "-") == 0)
		return (cd_target_from_oldpwd(envp, target, print_after));
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
