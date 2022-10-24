/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:37:01 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/24 14:39:34 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
		ft_printf("%s ", args[i]);
	ft_printf("\n");
}

char	*builtin_cd_get_dest(char *dest, t_ms_help *help)
{
	char	*tmp;

	if (!dest)
		tmp = get_env("HOME", help->env, help);
	else if (ft_strcmp("-", (const char *)dest) == 0)
		tmp = get_env("OLDPWD", help->env, help);
	else
		tmp = ft_strdup(dest);
	return (tmp);
}

void	builtin_cd_error_msg(char **str)
{
	struct stat	filestat;

	if (!access(*str, F_OK))
	{
		if (!(lstat(*str, &filestat)) && !(S_ISDIR(filestat.st_mode)))
			ft_printf("minishell: cd: not a directory: %s\n", *str);
		else
			ft_printf("minishell: cd: permission denied: %s\n", *str);
	}
	else
		ft_printf("minishell: cd: no such file or directory: %s\n", *str);
	ft_strdel(str);
}

void	builtin_cd(char **pwd, char *dest, t_ms_help *help)
{
	char	*tmp;

	tmp = builtin_cd_get_dest(dest, help);
	if (ft_strlen(tmp) == 0)
	{
		ft_strdel(&tmp);
		return ;
	}
	if (chdir(tmp) == -1)
	{
		builtin_cd_error_msg(&tmp);
		return ;
	}
	else
		update_env("OLDPWD", *pwd, &(help->env), help);
	ft_strdel(&tmp);
	ft_strdel(pwd);
	*pwd = getcwd(NULL, 0);
	if (dest)
	{
		if (ft_strcmp("-", (const char *)dest) == 0)
			ft_printf("%s\n", *pwd);
	}
	update_env("PWD", *pwd, &(help->env), help);
}

void	execute_commands(char ***args, t_ms_help *help)
{
	char	*buf;

	update_env("_", (*args)[help->arguments - 1], &(help->env), help);
	buf = getcwd(NULL, 0);
	if (ft_strcmp("exit", (*args)[0]) == 0)
	{
		ft_printf("BYE!\n");
		exit(0);
	}
	else if (ft_strcmp("echo", (*args)[0]) == 0)
		builtin_echo(*args);
	else if (ft_strcmp("cd", (*args)[0]) == 0)
		builtin_cd(&buf, (*args)[1], help);
	else if (ft_strcmp("env", (*args)[0]) == 0)
		print_env_list(help->env, help);
	else if (ft_strcmp("unsetenv", (*args)[0]) == 0)
		loop_unset_env(&(help->env), (*args), help);
	else if (ft_strcmp("setenv", (*args)[0]) == 0)
		set_env((*args), help);
	else
		execute_bins(args, help, &(help->env));
	ft_strdel(&buf);
}
