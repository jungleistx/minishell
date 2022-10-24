/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:33:29 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/24 14:29:44 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env_list(char **env, t_ms_help *help)
{
	char	**env_copy;
	int		env_size;

	env_size = ft_strarray_size(env);
	help->env_size = env_size;
	env_copy = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env_copy)
		exit(4);
	env_copy[env_size--] = NULL;
	while (env_size >= 0)
	{
		env_copy[env_size] = ft_strdup(env[env_size]);
		env_size--;
	}
	return (env_copy);
}

size_t	get_longest_env_len(char *name, char *env)
{
	size_t	len;
	size_t	name_len;

	len = 0;
	while (env[len] != '=' && env[len])
		len++;
	name_len = ft_strlen((const char *)name);
	if (name_len > len)
		len = name_len;
	return (len);
}

char	*get_env(char *name, char **env, t_ms_help *help)
{
	int		i;
	char	*tmp;
	size_t	env_len;

	i = 0;
	while (i < help->env_size)
	{
		env_len = get_longest_env_len(name, env[i]);
		if (ft_strncmp(env[i], name, env_len) == 0)
		{
			tmp = ft_strchr(env[i], 61);
			if (tmp[1])
				return (ft_strdup(&tmp[1]));
			return (ft_strdup(tmp));
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*get_full_env_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ((ft_isalnum(var[i])) || var[i] == '_'))
		i++;
	return (ft_strsub((const char *)var, 0, (size_t)i));
}
