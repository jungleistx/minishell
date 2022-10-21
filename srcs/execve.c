/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:43:30 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/21 15:23:18 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
