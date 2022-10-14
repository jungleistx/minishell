/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:33:29 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/12 11:31:47 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_list_size(char **env)
{
	int	total;

	total = 0;
	while (env[total])
		total++;
	return (total);
}

char	**copy_env_list(char **env, t_ms_help *help)
{
	char	**env_copy;
	int		env_size;

	env_size = get_env_list_size(env);
	help->env_size = env_size;
	env_copy = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env_copy)
		exit(4);

	// ft_printf("(env_size %d)\n", env_size);
	env_copy[env_size--] = NULL;
	while (env_size >= 0)
	{
		env_copy[env_size] = ft_strdup(env[env_size]);
		// ft_printf("(%s)\n(%s)\n\n", env[env_size], env_copy[env_size]);
		env_size--;
	}
	return (env_copy);
}

void	print_env_list(char **env, t_ms_help *help)
{
	int	i;

	i = 0;
	while (i < help->env_size)
		ft_printf("%s\n", env[i++]);
}

size_t	get_longest_env_len(char *name, char *env)
{
	size_t	len;

	len = 0;
	while (env[len] != '=' && env[len])
		len++;
	if (ft_strlen((const char *)name) > len)
		len = ft_strlen((const char *)name);
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

void	update_env(char *name, char *var, char ***env)
{
	int		a;
	char	*tmp;
	size_t	update_len;
	size_t	env_len;

	update_len = ft_strlen(name) + ft_strlen(var) + 2;
	a = -1;
	while ((*env)[++a])
	{
		env_len = get_longest_env_len(name, (*env)[a]);
		if (ft_strncmp((*env)[a], name, env_len) == 0)
		{
			ft_bzero((void *)tmp, update_len);
			ft_strdel(&(*env)[a]);
			tmp = (char *)malloc(sizeof(char) + update_len);
			if (!tmp)
				exit (5);
			ft_bzero((void *)tmp, update_len);
			tmp = ft_strcpy(tmp, (const char *)name);
			ft_strcat(tmp, "=");
			ft_strcat(tmp, var);
			(*env)[a] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
}

void	add_env(char *var, char ***env, t_ms_help *help)
{
	char	**new_env;
	int		size;

	help->env_size++;
	size = help->env_size;
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		exit(6);
	new_env[size--] = NULL;
	new_env[size] = ft_strdup(var);
	while (--size >= 0)
	{
		new_env[size] = ft_strdup((*env)[size]);
	}
	ft_free_doublearray(env);
	*env = new_env;
}
