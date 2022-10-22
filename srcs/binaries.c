/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:39:48 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/22 22:33:21 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_executable(char *path, char **command)
{
	struct stat	filestat;
	char		*new;
	int			ret_nr;

	new = ft_strjoin_three(path, "/", *command);
	if (!new)
		exit(18);
	ret_nr = 0;
	if (lstat(new, &filestat) == 0 && filestat.st_mode & S_IXUSR)
	{
		ft_strdel(command);
		*command = ft_strdup(new);
		ret_nr = 1;
	}
	ft_strdel(&new);
	return (ret_nr);
}

int	validate_paths(char ***env, char **command, t_ms_help *help)
{
	char		**paths;
	char		*name;
	int			i;

	name = get_env("PATH", *env, help);
	if (ft_strlen(name) == 0)
	{
		ft_strdel(&name);
		return (0);
	}
	paths = ft_strsplit((const char *)name, ':');
	ft_strdel(&name);
	if (!paths)
		exit(17);
	i = -1;
	while (paths[++i])
	{
		if (validate_executable(paths[i], command))
		{
			ft_free_doublearray(&paths);
			return (1);
		}
	}
	ft_free_doublearray(&paths);
	return (0);
}

int	validate_bin_name(char **command, char ***env, t_ms_help *help)
{
	struct stat	filestat;

	if ((*command)[0] == '/')
	{
		if (lstat(*command, &filestat) == 0 && filestat.st_mode & S_IXUSR)
			return (1);
	}
	else if (ft_strncmp("./", (const char *)*command, 2) == 0)
		return (1);
	else if (validate_paths(env, command, help))
		return (1);
	return (0);
}

void	execute_bins(char ***args, t_ms_help *help, char ***env)
{
	int		pid;
	char	*new;

	new = ft_strdup((const char *)(*args)[0]);
	if (validate_bin_name(&new, env, help))
	{
		pid = fork();
		if (pid < 0)
			ms_exit_error("ERROR fork < 0\n", 19);
		else if (pid == 0)
		{
			if (execve((const char *)new, *args, *env) == -1)
				ms_exit_error("ERROR on execve!\n", 20);
		}
		else
			wait(&pid);
	}
	else
		ft_printf("minishell: command not found: %s\n", (*args)[0]);
	ft_strdel(&new);
}
