/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:42:56 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/20 18:52:04 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_executable(char *path, char *command)
{
	struct stat	filestat;
	char		*new;
	int			ret_nr;

	new = ft_strjoin_three(path, "/", command);
	if (!new)
		exit(18);
	ret_nr = 0;
	if (lstat(new, &filestat) == 0 && filestat.st_mode & S_IXUSR)
		ret_nr = 1;
	ft_strdel(&new);
	return (ret_nr);
}

int	validate_paths(char ***env, char *command, t_ms_help *help)
{
	char		**paths;
	char		*name;
	int			i;

	name = get_env("PATH", *env, help);
	if (ft_strlen(name) == 0)
		return (0);
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

int	validate_bin_name(char *command, char ***env, t_ms_help *help)
{
	struct stat	filestat;

	if (command[0] == '/')
	{
		if (lstat(command, &filestat) == 0 && filestat.st_mode & S_IXUSR)
			return (1);
	}
	else if (validate_paths(env, command, help))
		return (1);
	return (0);
}
