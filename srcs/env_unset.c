/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:34:40 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/21 23:35:26 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_env_list_unset(char ***new, char ***env, char *name)
{
	int		i;
	int		j;
	size_t	len;

	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		len = get_longest_env_len(name, (*env)[i]);
		if (ft_strncmp((const char *)(*env)[i], name, len) == 0)
			continue ;
		(*new)[j] = ft_strdup((*env)[i]);
		if (!(*new)[j++])
			exit(16);
	}
	(*new)[j] = NULL;
}

void	unset_env(char ***env, char *name, t_ms_help *help)
{
	char	*tmp;
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = get_env(name, *env, help);
	if (ft_strlen(tmp) == 0)
	{
		ft_strdel(&tmp);
		return ;
	}
	new = (char **)malloc(sizeof(char *) * help->env_size);
	if (!new)
		exit(15);
	copy_env_list_unset(&new, env, name);
	help->env_size--;
	ft_free_doublearray(env);
	*env = new;
	ft_strdel(&tmp);
}

void	loop_unset_env(char ***env, char **args, t_ms_help *help)
{
	int	i;

	i = 0;
	while (++i < help->arguments)
		unset_env(env, args[i], help);
}
